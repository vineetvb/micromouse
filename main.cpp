#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include "maze.h"
#include "mouse.h"

void randomizeMaze(Maze& M)
{
    int size = M.getSize();
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, size-1);
    int randwalls = size/8;
    int randsamples = size * size;    
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
                M.setLeftWall(jr, ir);
                break;
            case 1:
                M.setRightWall(jr, ir);
                break;
            case 2:
                M.setUpWall(jr, ir);
                break;
            case 3:
                M.setDownWall(jr, ir);
            }
        }
    }
}

 
int main()
{
    std::cout << "Running Micromouse" << std::endl;

    // Make a Maze
    int mazeSize = 16;
    Maze maze(mazeSize);
    maze.makeBoundaryWalls();
    randomizeMaze(maze);

    // Make a mouse
    Mouse mouse;

    // PLace Mouse in Maze
    maze.addMouse(&mouse);
    
    maze.draw(false);    
    mouse.turn(-90);    
    
    for (int i = 0; i < 4; ++i)
    {
        //mouse.internalMaze->draw();
        mouse.readSensors(&maze);
        mouse.show();
        mouse.advance();
    }
    
    return 0;
}
