#ifndef MOUSE_H_
#define MOUSE_H_

#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include "maze.h"
#include "sensor.h"

#define _USE_MATH_DEFINES

float deg2rad(int deg);

class Maze;
class Sensor;

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
      std::cout << "Sensors: F " << int(sensorOutputs[0]) << std::endl;
      //<< " " << int(sensorOutputs[1])
      //		<< " " << int(sensorOutputs[2]) << std::endl << "```````````" << std::endl;
    }
    

    void updateTf();
    void advance();
    void readSensors(Maze const* refMaze);
    
    //current x,y, theta position
    int cx, cy, ctheta;
    
    std::array<int, 4> Tf;

    // Sensors on this mouse
    std::vector<Sensor> sensors;

    std::vector<bool> sensorOutputs;
    
};

#endif
