#include "sensor.h"
#include "maze.h"

char
Sensor::
readReferenceMaze(Maze const* refMaze)
{
        // sensor always reads at position [1,0] relative to its own
        // frame of reference
        if (ctheta == 0) // facing LEFT
            return refMaze->getLeftWall(cx, cy);
        if (ctheta == 90 ) // facing UP
            return refMaze->getUpWall(cx, cy);
        if (ctheta == 180) // facing RGIHT
            return refMaze.>getRightWall(cx, cy);
        if (ctheta == 270) // facing DOWN
            return refMaze->getDownWall(cx, cy);
}

