#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "maze.h"

#include <cimg/CImg.h>
class Maze;

class Simulation
{
public:
    Simulation(int h, int w, int _scale):imgHeight(h), imgWidth(w), imgScale(_scale)
    {
        image = cimg_library::CImg<unsigned char>(imgHeight, imgWidth, 1, 3, 0);
	image.fill(0);
    };

    void render(Maze const * maze);

    // store coords of previous render to erase before calling this render
    void render(Mouse const* mouse);

    cimg_library::CImgDisplay display;

    void scaleAndDisplay();
    
 private:
    // helper method that draws cell, should probably be private
    void render(Maze const* maze, int x, int y, const unsigned char* color);
    int xprev, yprev;
    
    cimg_library::CImg<unsigned char> image;

        
    int imgHeight;

    int imgWidth;

    int imgScale;
    
  
};

#endif
