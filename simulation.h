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
    
    cimg_library::CImg<unsigned char> image;

    cimg_library::CImgDisplay display;
    
    int imgHeight;

    int imgWidth;

    int imgScale;
    
  
};

#endif
