#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "command.h"
#include "mouse.h"
#include "maze.h"

#include <random>
#include <queue>

class Mouse;
class FloodMaze;
class Maze;


class Algorithm
{
public:
    //Algorithm();
    virtual const CommandI process() = 0;
    virtual void init() {};
    const Mouse * mouse;
};


class RandomExplorerAlgorithm : public Algorithm
{
public:
    RandomExplorerAlgorithm()
    {
      std::random_device rd;  //Will be used to obtain a seed for the random number engine
      gen = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
      dis = std::uniform_int_distribution<>(0, 9);
    };
    const CommandI process();

private:
    std::uniform_int_distribution<> dis;
    std::mt19937 gen;

};

struct MazeNode
{
    int x, y, val;
//    MazeNode * prev;
    MazeNode(int _x, int _y, int _val): x(_x), y(_y), val(_val)
    {

    };
    MazeNode(): x(0), y(0), val(0){};


};

class FloodFillExplorationAlgorithm : public Algorithm
{
public:
    FloodFillExplorationAlgorithm();
    const CommandI process();

    void flood();

    void show();

    void backtrack(std::vector<MazeNode>& path);

    virtual void init();



private:
    Maze * maze;
    std::vector<char> visited;
    std::vector<int> floodVal;
    int size;
    int xGoal, yGoal;

    void updateMazeNode(MazeNode& e, MazeNode& n, std::queue<MazeNode>& q);

};




#endif
