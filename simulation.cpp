
#include "simulation.h"

using namespace cimg_library;

// helper function to draw cells when rendering maze
void Simulation::render(Maze const* maze, int x, int y, const unsigned char* color)
{
    int xl = std::max(0, 8 * x);
    int xr = xl + 8;

    int yt = (15 - y) * 8;
    int yb = yt + 8;

    if (maze->getUpWall(x, y))
        image.draw_line(xl, yt, xr, yt, color);
    if (maze->getLeftWall(x, y))
        image.draw_line(xl, yt, xl, yb, color);
    if (maze->getDownWall(x, y))
        image.draw_line(xl, yb, xr, yb, color);
    if (maze->getRightWall(x, y))
        image.draw_line(xr, yb, xr, yt, color);

    // Draw the post in the bottom left corner
    image(xl, yb, 1) = 200;
    image(xl, yb, 2) = 200;
    image(xl, yb, 0) = 200;
}

void Simulation::render(Maze const* maze)
{
    const unsigned char red[] = {200, 10, 20 };

    int size = maze->getSize();
    
    for (int x = 0; x < size; ++x)
    {
        for (int y = 0; y < size; ++y)
        {
            render(maze, x, y, red);
        }
    }
}

void Simulation::render(Mouse const* mouse)
{
    // first erase the pixels from the previous render
    int xc = xprev;
    int yc = yprev;

    // ToDO: check block erase
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            image(xc + i, yc + j, 2) = 0;
        }
    }

    // Now start drawing the mouse for this render
    // (xc, yc) is the topleft pixel of the 3xx mouse image
    xc = 8*mouse->getX() + 4 - 1;
    yc = 8*(15 - mouse->getY()) + 4 - 1;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            image(xc + i, yc + j, 2) = 250;
        }
    }

    switch(mouse->getTheta())
    {
    case 0:
        image(xc + 2, yc + 1, 1) = 250;
        break;
    case 90:
        image(xc + 1, yc, 1) = 250;
        break;
    case 180:
        image(xc, yc + 1, 1) = 250;
        break;
    case 270:
        image(xc + 1, yc + 2, 1) = 250;
        break;
    }

    xprev = xc;
    yprev = yc;
    
}

void Simulation::scaleAndDisplay()
{
    CImg<unsigned char> imageScaled = image.get_resize(imgHeight*imgScale, imgWidth*imgScale);
    imageScaled.display(display);
}
