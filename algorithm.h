#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "command.h"
#include "mouse.h"

class Mouse;

class Algorithm
{
public:
    //Algorithm();
    virtual const CommandI process() = 0;
};


class RandomExplorerAlgorithm : public Algorithm
{
public:
    RandomExplorerAlgorithm()
    {
    };

    const CommandI process();

    const Mouse * mouse;

};



#endif
