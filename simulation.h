#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "maze.h"

#include <cimg/CImg.h>
class Maze;

#define MMPERPIXEL 6
#define CELLWIDTH_MM 180 // Each square cell is 18 cm
#define POSTWIDTH_MM 12
#define MOUSEWIDTH_MM 60 // only square mouse is supported currently

class Simulation
{
public:
  Simulation()
  {
       imgHeight = (CELLWIDTH_MM * MAZESIZE) / MMPERPIXEL + 50;
       imgWidth = (CELLWIDTH_MM * MAZESIZE) / MMPERPIXEL + 50;
       imgScale = 1;
       image = cimg_library::CImg<unsigned char>(imgHeight, imgWidth, 1, 3, 0);
       image.fill(0);
       xprev = 0;
       yprev = 0;
  };

    void render(Maze const * maze, const unsigned char * color);

    // store coords of previous render to erase before calling this render
    void render(Mouse const* mouse);

    cimg_library::CImgDisplay display;

    void scaleAndDisplay();

    void saveBMP(std::string& fileName);
    void saveBMP();

    // private:
    // helper method that draws cell, should probably be private
    void render(Maze const* maze, int x, int y, const unsigned char* color);
    int xprev, yprev;

    cimg_library::CImg<unsigned char> image;


    int imgHeight;

    int imgWidth;

    int imgScale;

    static int frameNumber;

};

#endif
