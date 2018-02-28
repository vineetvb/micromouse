
#include "maze.h"
#include <iostream>
#include <fstream>

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
    if(x>0)
        setBits(at(x - 1, y), rightWallMask);
}

char Maze::getLeftWall(int x, int y) const
{
    return getBits(at(x, y), leftWallMask);
}

void Maze::setRightWall(int x, int y)
{
    setBits(at(x, y), rightWallMask);
    if (x < size - 1)
        setBits(at(x + 1, y), leftWallMask);
}

char Maze::getRightWall(int x, int y) const
{
    return getBits(at(x, y), rightWallMask);
}

void Maze::setUpWall(int x, int y)
{
    setBits(at(x, y), upWallMask);
    if ( y < size - 1)
        setBits(at(x, y + 1), downWallMask);
}

char Maze::getUpWall(int x, int y) const
{
    return getBits(at(x, y), upWallMask);
}


void Maze::setDownWall(int x, int y)
{
    setBits(at(x, y), downWallMask);
    if (y>0)
        setBits(at(x, y - 1), upWallMask);
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

void Maze::randomizeWalls()
{
    using namespace std;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, size-1);
    int randwalls = size/16;
    int randsamples = size * size / 2;
    for (int i=0; i < randsamples; ++i)
    {
        int ir = dis(gen);
        int jr = dis(gen);
        for (int l = 0; l < randwalls; ++l)
        {
            int lr = dis(gen);
            switch (lr%4)
            {
            case 0:
                setLeftWall(jr, ir);
                if (jr > 0 )
                    setRightWall(jr-1, ir);
                break;
            case 1:
                setRightWall(jr, ir);
                if (jr < size - 1)
                    setLeftWall(jr + 1, ir);
                break;
            case 2:
                setUpWall(jr, ir);
                if (ir < size - 1)
                    setDownWall(jr, ir + 1);
                break;
            case 3:
                setDownWall(jr, ir);
                if (ir > 0)
                    setUpWall(jr, ir - 1);
            }
        }
    }
}

void Maze::fromMazeFile(const std::string& mazeFileName)
{
    std::ifstream mazeFile(mazeFileName.c_str(), std::ios::binary);
    char f[256];
    mazeFile.read(f, 256);
    for ( int i = 0; i < size; ++i)
    {
        for ( int j = 0; j < size; ++j)
        {
            char c = f[i*size + j];
            setBits(at(i, j), c );
        }
    }
}

int& FloodMaze::operator()(int x, int y)
{
    int * a = floodVal.get();
    return a[y*size + x];
}



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

    std::cout << mazeStr << std::endl;
}
