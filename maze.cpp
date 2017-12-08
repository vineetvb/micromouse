
#include "maze.h"
#include <iostream>

Maze::
Maze(int _size): size(_size)
{
    std::cout << "Creating Maze of size: " << size << std::endl;
    walls = std::unique_ptr<char[]>(new char[size * size]());
}


void
Maze::
setBits(char& node, const char& mask)
{
    node |= mask;
}

char
Maze::
getBits(char const& node, const char& mask) const
{
    return node & mask;
}

bool
Maze::
isWall(char const& maskedNode) const
{
    return maskedNode > 0;
}

bool
Maze::
isLeftWall(int x, int y) const
{
    return isWall( getBits(at(x, y), leftWallMask) );
}

bool
Maze::
isRightWall(int x, int y) const
{
    return isWall( getBits( at(x, y), rightWallMask) );
}

bool
Maze::
isUpWall(int x, int y) const
{
    return isWall( getBits(at(x, y), upWallMask) );
}

bool
Maze::
isDownWall(int x, int y) const
{
    return isWall( getBits(at(x, y), downWallMask) );
}

char&
Maze::
at(int x, int y) const
{
    char * a = walls.get();
    return a[y*size + x];
}

void
Maze::
setLeftWall(int x, int y)
{
    setBits(at(x, y), leftWallMask);
}

char
Maze::
getLeftWall(int x, int y) const
{
    return getBits(at(x, y), leftWallMask);
}

void
Maze::
setRightWall(int x, int y)
{
    setBits(at(x, y), rightWallMask);
}

char
Maze::
getRightWall(int x, int y) const
{
    return getBits(at(x, y), rightWallMask);
}

    

void
Maze::
setUpWall(int x, int y)
{
    setBits(at(x, y), upWallMask);
}

char
Maze::
getUpWall(int x, int y) const
{
    return getBits(at(x, y), upWallMask);
}


void
Maze::
setDownWall(int x, int y)
{
    setBits(at(x, y), downWallMask);
}

char
Maze::
getDownWall(int x, int y) const
{
    return getBits(at(x, y), downWallMask);
}

void
Maze::
makeBoundaryWalls(void)
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

std::string
Maze::
drawCell(int x, int y)
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


void
Maze::draw(bool drawMouse)
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
        int x = mouse->cx, y = size - 1 -mouse->cy;
        int pos = 2 * size * y + y + 2 * x;
        //std::cout <<mazeStr.size() << "" << x << " " << y << " " << pos << std::endl;
        mazeStr.at(pos) = mazeStr.at(pos)=='_' ? 'E' : 'F';
    }

    std::cout << mazeStr << std::endl;
    
                        
}


