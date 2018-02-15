/*
  Micromouse Simulator and Maze Solver
  Copyright (C) 2017  Vineet Bhatawadekar

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <thread>
#include <chrono>

#include "maze.h"
#include "mouse.h"

void randomizeMaze(Maze& M)
{
    int size = M.getSize();
    using namespace std;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, size-1);
    int randwalls = size/16;
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
                if (jr > 0 )
                    M.setRightWall(jr-1, ir);
                break;
            case 1:
                M.setRightWall(jr, ir);
                if (jr < size - 1)
                    M.setLeftWall(jr + 1, ir);
                break;
            case 2:
                M.setUpWall(jr, ir);
                if (ir < size - 1)
                    M.setDownWall(jr, ir + 1);
                break;
            case 3:
                M.setDownWall(jr, ir);
                if (ir > 0)
                    M.setUpWall(jr, ir - 1);
            }
        }
    }
}


int main()
{
    using namespace std;
    cout << "Running Micromouse" << endl;

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
    cout << " Reference Maze" << endl;

    mouse.turn(-90);

    for (int i = 0; i < 10; ++i)
    {

        maze.draw();
        mouse.readSensors(&maze);
        mouse.show();

        bool success = mouse.advance(&maze);
        if(!success)
        {
            cout << " COLLISION WARNING " << endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        //std::cout << std::flush << std::endl;

    }

    return 0;
}
