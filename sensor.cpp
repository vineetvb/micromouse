#include "sensor.h"
#include "maze.h"

bool
Sensor::
readReferenceMaze(Maze const* refMaze)
{
        // sensor always reads at position [1,0] relative to its own
        // frame of reference
        if (ctheta == 0) // facing RIGHT
            return refMaze->isRightWall(cx, cy);
        if (ctheta == 90 ) // facing UP
            return refMaze->isUpWall(cx, cy);
        if (ctheta == 180) // facing LEFT
            return refMaze->isLeftWall(cx, cy);
        if (ctheta == 270) // facing DOWN
            return refMaze->isDownWall(cx, cy);
}

