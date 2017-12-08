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

    // these are relative positions of sensor
    // w.r.t to the mouse
    Sensor(int _cx, int _cy, int _ctheta)
    {
      cx = _cx;
      cy = _cy;
      _ctheta = ctheta;
    }

  bool readReferenceMaze(Maze const* refMaze);
    
};

#endif
