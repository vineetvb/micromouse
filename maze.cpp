
#include "maze.h"
#include <iostream>

Maze::Maze(int _size): size(_size)
{
    std::cout << "Creating Maze of size: " << size << std::endl;
    walls = std::unique_ptr<char[]>(new char[size * size]());
    for (int i =0; i < size*size; ++i)
    {
        walls.get()[i] = 0;
    }
}


/* Member functions used to manipulate maze walls */
void Maze::setBits(char& node, const char& mask)
{
    node |= mask;
}

char Maze::getBits(char const& node, const char& mask) const
{
    return node & mask;
}

bool Maze::isWall(char const& maskedNode) const
{
    return maskedNode > 0;
}

bool Maze::isLeftWall(int x, int y) const
{
    return isWall( getBits(at(x, y), leftWallMask) );
}

bool Maze::isRightWall(int x, int y) const
{
    return isWall( getBits( at(x, y), rightWallMask) );
}

bool Maze::isUpWall(int x, int y) const
{
    return isWall( getBits(at(x, y), upWallMask) );
}

bool Maze::isDownWall(int x, int y) const
{
    return isWall( getBits(at(x, y), downWallMask) );
}

char& Maze::at(int x, int y) const
{
    char * a = walls.get();
    return a[y*size + x];
}

void Maze::setLeftWall(int x, int y)
{
    setBits(at(x, y), leftWallMask);
}

char Maze::getLeftWall(int x, int y) const
{
    return getBits(at(x, y), leftWallMask);
}

void Maze::setRightWall(int x, int y)
{
    setBits(at(x, y), rightWallMask);
}

char Maze::getRightWall(int x, int y) const
{
    return getBits(at(x, y), rightWallMask);
}

void Maze::setUpWall(int x, int y)
{
    setBits(at(x, y), upWallMask);
}

char Maze::getUpWall(int x, int y) const
{
    return getBits(at(x, y), upWallMask);
}


void Maze::setDownWall(int x, int y)
{
    setBits(at(x, y), downWallMask);
}

char Maze::getDownWall(int x, int y) const
{
    return getBits(at(x, y), downWallMask);
}

void Maze::makeBoundaryWalls(void)
{
    // Left Boundary Wall
    for(int y = 0; y < size; ++y)
    {
        setLeftWall(0, y);
    }

    // Right Boundary Wall
    for(int y = 0; y < size; ++y)
    {
        setRightWall(size -1, y);
    }

    // South wall
    for(int x = 0; x < size; ++x)
    {
        setDownWall(x, 0);
    }

    // North Wall
    for(int x = 0; x < size; ++x)
    {
        setUpWall(x, size - 1);
    }
}

/* Member functions for physical interaction with a Mouse */


void Maze::addMouse(Mouse const* mouseIn)
{
    this->mouse = mouseIn;
};




/* Member Functions that help to visualize */
std::string Maze::drawCell(int x, int y)
{
    std::string s ="";

    bool L = getLeftWall(x, y),
        R = getRightWall(x,y),
        U = getUpWall(x ,y),
        D = getDownWall(x, y);

    if (D)
        s += "_";
    else
        s += " ";

    if (R)
        s += "|";
    else
        s += " ";

    return s;
}


void Maze::draw(bool drawMouse)
{
    std::cout << std::string(size*2 - 1, '_') << std::endl;
    std::string mazeStr = "";

    for (int i = size - 1; i>=0; --i )
    {
        std::string row = "";
        for ( int j = 0; j < size; ++j)
        {
            row += drawCell(j, i);
        }
        mazeStr += row;
        mazeStr += "\n";
    }

    if(drawMouse)
    {
        int x = mouse->getX(), y = size - 1 -mouse->getY();
        int pos = 2 * size * y + y + 2 * x;
        mazeStr.at(pos) = mazeStr.at(pos)=='_' ? 'E' : 'F';
    }

    std::cout << mazeStr << std::endl;
}


using namespace cimg_library;

void Maze::drawCellImage(CImg<unsigned char>& img, int x, int y, unsigned char const* color)
{
    int xl = std::max(0, 8 * x);
    int xr = xl + 8;

    int yt = (15 - y) * 8;
    int yb = yt + 8;

    if (getUpWall(x, y))
        img.draw_line(xl, yt, xr, yt, color);
    if (getLeftWall(x, y))
        img.draw_line(xl, yt, xl, yb, color);
    if (getDownWall(x, y))
        img.draw_line(xl, yb, xr, yb, color);
    if (getRightWall(x, y))
        img.draw_line(xr, yb, xr, yt, color);

    img(xl, yb, 1) = 200;
    img(xl, yb, 2) = 200;
    img(xl, yb, 0) = 200;

}

void Maze::drawMouse(CImg<unsigned char>& img)
{
    // (xc, yc) is the topleft pixel of the 3xx mouse image
    int xc = 8*mouse->getX() + 4 - 1;
    int yc = 8*(15 - mouse->getY()) + 4 - 1;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            img(xc + i, yc + j, 2) = 250;
        }
    }

    switch(mouse->getTheta())
    {
    case 0:
        img(xc + 2, yc + 1, 1) = 250;
        break;
    case 90:
        img(xc + 1, yc, 1) = 250;
        break;
    case 180:
        img(xc, yc + 1, 1) = 250;
        break;
    case 270:
        img(xc + 1, yc + 2, 2) = 250;
        break;
    }



}

void Maze::drawImage(CImg<unsigned char>& img, bool mouseDraw)
{
    const unsigned char red[] = {200, 10, 20};
    const unsigned char green[] = {20, 200, 20};
    const unsigned char gray[] = {200, 200, 200};

    for (int x = 0; x < size; ++x)
    {
        for (int y = 0; y < size; ++y)
        {
            drawCellImage(img, x, y, red);
        }
    }

    if (mouseDraw)
    {
        drawMouse(img);
    }
}
