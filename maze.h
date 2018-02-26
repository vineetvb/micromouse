#ifndef MAZE_H_
#define MAZE_H_
#include <memory>

#include "mouse.h"

#include <cimg/CImg.h>

class Mouse;

class Maze
{
private:
    int size;

    // Maze is represented as set of cells/node. Each node can be
    // 4-connected with its neighbors. The last 4 bits of the char
    // value store its LRUD connectivity as 0b0000LRUD.
    std::unique_ptr<char[]> walls;

    // helper method to set wall bit masks
    void setBits(char& node, const char& wallMask);
    char getBits(char const& node, const char& wallMask) const;
    const char leftWallMask  = 0b00001000;
    const char rightWallMask = 0b00000100;
    const char upWallMask    = 0b00000010;
    const char downWallMask  = 0b00000001;

public:
    /** 
	Return a reference to the node at (x,y).
        The nodes are arranged in row-major order from bottom-left node
        which is the origin at (0,0), X-axis points right, Y axis
        points up.
	\param x: x position >
        \param y: y position of cell ^
        \returns char indicating wall bits
    */
    char& at(int x, int y) const;

    void setLeftWall(int x, int y);
    char getLeftWall(int x, int y) const;
    void setRightWall(int x, int y);
    char getRightWall(int x, int y) const;
    void setUpWall(int x, int y);
    char getUpWall(int x, int y) const;
    void setDownWall(int x, int y);
    char getDownWall(int x, int y) const;

    bool isWall(char const& maskedNode) const;
    bool isRightWall(int x, int y) const;
    bool isLeftWall(int x, int y) const;
    bool isUpWall(int x, int y) const;
    bool isDownWall(int x, int y) const;

    void makeBoundaryWalls(void);

    // To be removed
    std::string drawCell(int x, int y);
    void draw(bool drawMouse = true);

    /// Return the number of cells along one dimension
    int getSize(void) const  {return size;};

    /** Places mouse physically in the maze.
	Default location is wherever the input mouse is designed to start from.
    */
    void addMouse(Mouse const* mouseIn);

    Maze(int _size);

    Mouse const* mouse;


};

#endif
