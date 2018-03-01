#ifndef MAZE_H_
#define MAZE_H_
#include <memory>

#define MAZESIZE 16
#include "mouse.h"
class Mouse;

class Maze
{

private:
    // Maze is represented as set of cells/node. Each node can be
    // 4-connected with its neighbors. The last 4 bits of the char
    // value store its LRUD connectivity as 0b0000LRUD.
    std::unique_ptr<char[]> walls;

    // helper method to set wall bit masks
    void setBits(char& node, const char& wallMask);
    char getBits(char const& node, const char& wallMask) const;

    // Same convention as outlined here
    // https://github.com/micromouseonline/micromouse_maze_tool
    const char leftWallMask  = 0x08 ;
    const char rightWallMask = 0x02 ;
    const char upWallMask    = 0x01 ;
    const char downWallMask  = 0x04 ;

protected:
    int size;

public:
    /**
	Return a reference to the node at (x,y).
        The nodes are arranged in row-major order from bottom-left node
        which is the origin at (0,0), X-axis points right, Y axis
        points up.
	\param x: x position >
        \param y: y position of cell ^
        \returns char indicating wall bits
    */
    char& at(int x, int y) const;

    void setLeftWall(int x, int y);
    char getLeftWall(int x, int y) const;
    void setRightWall(int x, int y);
    char getRightWall(int x, int y) const;
    void setUpWall(int x, int y);
    char getUpWall(int x, int y) const;
    void setDownWall(int x, int y);
    char getDownWall(int x, int y) const;

    bool isWall(char const& maskedNode) const;
    bool isRightWall(int x, int y) const;
    bool isLeftWall(int x, int y) const;
    bool isUpWall(int x, int y) const;
    bool isDownWall(int x, int y) const;

    void makeBoundaryWalls(void);
    void randomizeWalls(void);

    void fromMazeFile(std::string const& mazeFileName);

    // To be removed
    std::string drawCell(int x, int y);
    void draw(bool drawMouse = true);

    /// Return the number of cells along one dimension
    int getSize(void) const  {return size;};

    /** Places mouse physically in the maze.
	Default location is wherever the input mouse is designed to start from.
    */
    //void addMouse(Mouse * mouseIn);

    Maze(int _size);

};

struct Node
{
    int x, y, val;
    Node(int _x, int _y, int _val): x(_x), y(_y), val(_val)
        {
        };
    Node(): x(0), y(0), val(0){};

};



class FloodMaze : public Maze
{
public:
    FloodMaze(int _size): Maze(_size)
    {
        std::cout << "Creating Flood Maze of size: " << size << std::endl;
        floodVal = std::unique_ptr<int[]>(new int[size * size]());
        for (int i =0; i < size*size; ++i)
        {
            floodVal.get()[i] = 0;
        }
        xGoal = (size-1)/2;
        yGoal = (size-1)/2;
    }

    void setXGoal(int x) {xGoal = x;};
    void setYGoal(int y) {yGoal = y;};

    int& operator()(int x, int y);

    void flood();


private:
    std::unique_ptr<int[]> floodVal;

    int xGoal, yGoal;

};


#endif
