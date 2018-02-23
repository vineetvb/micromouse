#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "maze.h"

#include <cimg/CImg.h>

class Simulation
{
public:
    Simulation(int h, int w, int _scale):imgHeight(h), imgWidth(w), scale(_scale)
    {
        image = cimg_library::CImg<unsigned char>(imgHeight, imgWidth, 1, 3, 0);
    };

    void render(Maze const* maze);
    
    cimg_library::CImg<unsigned char> image;

    cimg_library::CImgDisplay display;
    
    int imgHeight;

    int imgWidth;

    int scale;
    
  
};

#endif
