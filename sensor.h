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
    
};

