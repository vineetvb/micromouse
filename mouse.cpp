#include "mouse.h"
float deg2rad(int deg)
{
    return M_PI * (static_cast<float>(deg) / 180.0);
}

Mouse::
Mouse(void): cx(0), cy(0), ctheta(90)
{
    updateTf();
    internalMaze = new Maze(16);
    internalMaze->mouse = this;
    internalMaze->makeBoundaryWalls();
    
}

// advance forward by 1 position
void
Mouse::
advance(void)
{
    cx = Tf[0]*1 + Tf[1]*0 + cx;
    cy = Tf[2]*1 + Tf[3]*0 + cy;
}

void
Mouse::
updateTf()
{
    Tf[0] = std::cos(deg2rad(ctheta));
    Tf[1] = -std::sin(deg2rad(ctheta));
    Tf[2] = std::sin(deg2rad(ctheta));
    Tf[3] = std::cos(deg2rad(ctheta));
}




