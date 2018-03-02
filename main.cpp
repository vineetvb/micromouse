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

int Simulation::frameNumber = 0;

int main()
{
    using namespace std;
    cout << "Running Micromouse" << endl;

    // Make a Maze
    int mazeSize = 16;
    Maze maze(mazeSize);
    maze.makeBoundaryWalls();
    maze.fromMazeFile("/home/vbhatawadekar/code/micromouse/mazefiles/hitel51.maz");

    // Make a mouse
    Mouse mouse;

    // Set it explore randomly
    RandomExplorerAlgorithm explore;

    // Floodfill exploration
    FloodFillExplorationAlgorithm ff;
    mouse.setAlgorithm(&ff);
    
    // Create the Simulation object
    // Simulation display size params are in simulation.h
    Simulation sim;

    // Start maze simulation
    mouse.start(&maze, &sim);

    return 0;
}
