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

#include "maze.h"
#include "mouse.h"
#include <iomanip>      // std::setw

void testFF()
{
    using namespace std;
    FloodMaze maze(4);
    maze.makeBoundaryWalls();
    maze.setRightWall(0,0);
    maze.setRightWall(2,0);
    maze.setLeftWall(3,3);
    maze.setUpWall(1, 0);
    maze.setRightWall(1,1);
    maze.setDownWall(0, 2);
    maze.setRightWall(0,3);
    maze.setDownWall(1,3);
    maze.setDownWall(3,2);
    maze.setXGoal(3); maze.setYGoal(3);
}


int main()
{
    using namespace std;
    cout << "Running Micromouse" << endl;

    // Make a Maze
    int mazeSize = 16;
    Maze maze(mazeSize);
    maze.makeBoundaryWalls();
    maze.fromMazeFile("/home/vineet/code/micromouse/mazefiles/hoku4.maz");

    // Make a mouse
    Mouse mouse;

    // Set it explore randomly
    RandomExplorerAlgorithm explore;
    std::cout << " 1 " << std::endl;

    FloodFillExplorationAlgorithm ff;
    mouse.setAlgorithm(&ff);


    std::cout << " 3 " << std::endl;


    // Create the Simulation object
    // Simulation display size is currently fixed to 144x144
    Simulation sim;

    // Start maze simulation*/
    mouse.start(&maze, &sim);

    return 0;
}
