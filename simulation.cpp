
#include "simulation.h"

using namespace cimg_library;

void Simulation::render(Maze const* maze)
{
    image.fill(0);
    
    maze->drawImage(image);
    CImg<unsigned char> imageScaled = image.get_resize(imgHeight*imgScale, imgWidth*imgScale);
    imageScaled.display(display);
}
