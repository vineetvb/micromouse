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

int main()
{
    using namespace std;
    cout << "Running Micromouse" << endl;

    // Make a Maze
    int mazeSize = 16;
    Maze maze(mazeSize);
    maze.makeBoundaryWalls();
    maze.fromMazeFile("/home/vbhatawadekar/code/micromouse/hoku4.maz");
    // Make a mouse
    Mouse mouse;

    // Set it explore randomly
    RandomExplorerAlgorithm explore;
    mouse.setAlgorithm(&explore);

    // Place Mouse in Maze
    maze.addMouse(&mouse);

    // Create the Simulation object
    // Simulation display size is currently fixed to 144x144
    Simulation sim;

    sim.render(&maze);
    
    const unsigned char green[] = {50, 50, 50};
    const unsigned char black[] = {0, 0, 0};
    //sim.image.draw_text(3, 3, "824", green, black, 1.0f, 13);

    sim.scaleAndDisplay();

    sim.image.save_bmp("/home/vbhatawadekar/code/micromouse/maze.bmp");
    

    //while (!sim.display.is_closed())
    {
    }
    
    // Start maze simulation*/
    mouse.start(&maze, &sim);

    return 0;
}
