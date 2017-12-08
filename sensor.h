#ifndef SENSOR_H_
#define SENSOR_H_

#include "maze.h"

class Maze;
class Mouse;

// Single Directional wall sensor

class Sensor
{
public:
    int cx, cy, ctheta;
    Sensor(): cx(0), cy(0), ctheta(0)
    {
    };

    // this is relative position of sensor
    // w.r.t to the mouse
    Sensor(int _cx, int _cy, int _ctheta)
    {
      cx = _cx;
      cy = _cy;
      ctheta = _ctheta;
    };

  bool readReferenceMaze(Maze const* refMaze);

  Mouse const* mouse;
    
};

#endif
