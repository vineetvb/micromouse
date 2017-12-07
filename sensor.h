#ifndef SENSOR_H_
#define SENSOR_H_

#include "maze.h"
class Maze;

// Single Directional wall sensor

class Sensor
{
public:
    int cx, cy, ctheta;
    Sensor(): cx(0), cy(0), ctheta(0)
    {
    };
    
    

private:
  char readReferenceMaze(Maze const* refMaze);
    
};

#endif
