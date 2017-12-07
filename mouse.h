#ifndef MOUSE_H_
#define MOUSE_H_

#include <array>
#include <cmath>
#include <iostream>
#include "maze.h"

#define _USE_MATH_DEFINES

float deg2rad(int deg);

class Maze;

class Mouse
{
public:
    Mouse(void);
    
    // internal representation of explored maze
    Maze* internalMaze;

    void readWalls();

    void turn(int theta)
    {
        ctheta += theta;
        ctheta = ctheta % 360;
        updateTf();
    };

    void show()
        {
            std::cout << "Mouse: x, y, theta " << cx << " " << cy << " " << ctheta << std::endl;
            
        }
    

    void updateTf();
    void advance();
    

    //current x,y, theta position
    int cx, cy, ctheta;
    
    std::array<int, 4> Tf;
    

    
  
};

#endif
