#include "sensor.h"
#include "maze.h"
using namespace std;

bool Sensor::readReferenceMaze(Maze const* refMaze)
{
    // compute absolute position of this sensor w.r.t to the mouse on
    // which it is mounted
    int x = mouse->getX();
    int y = mouse->getY();
    int theta = (mouse->getTheta() + this->ctheta + 360) % 360;

    // sensor always reads at position [1,0] relative to its own
    // frame of reference
    if (theta == 0) // facing RIGHT
    {
        return refMaze->isRightWall(x, y);
    }

    if (theta == 90 ) // facing UP
    {
        return refMaze->isUpWall(x, y);
    }

    if (theta == 180) // facing LEFT
    {
        return refMaze->isLeftWall(x, y);
    }

    if (theta == 270) // facing DOWN
    {
        return refMaze->isDownWall(x, y);
    }
}
