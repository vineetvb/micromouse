#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "command.h"
#include "mouse.h"
#include <random>

class Mouse;

class Algorithm
{
public:
    //Algorithm();
    virtual const CommandI process() = 0;
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

    std::uniform_int_distribution<> dis;
    std::mt19937 gen;

};

class FloodFillExplorationAlgorithm : public Algorithm
{

};




#endif
