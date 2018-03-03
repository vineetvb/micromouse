
#include "simulation.h"

using namespace cimg_library;

// helper function to draw cells when rendering maze
void Simulation::render(Maze const* maze, int x, int y, const unsigned char* color)
{
    int pixelScale = CELLWIDTH_MM / MMPERPIXEL;
    int postSizePixels = POSTWIDTH_MM / MMPERPIXEL;

    int xl = pixelScale * x;
    int xr = xl + pixelScale;

    int yt = (MAZESIZE - 1 - y) * pixelScale;
    int yb = yt + pixelScale;

    if (maze->getUpWall(x, y))
    {
        for (int i = 0; i < postSizePixels; ++i)
        {
            image.draw_line(xl, yt + i, xr, yt + i, color);
        }
    }

    if (maze->getLeftWall(x, y))
    {
        for (int i = 0; i < postSizePixels; ++i)
        {
            image.draw_line(xl + i, yt, xl + i, yb, color);
        }
    }

    // Draw the post in the bottom left corner
    for ( int i = 0; i < postSizePixels; ++i)
    {
        for ( int j = 0; j < postSizePixels; ++j)
        {
            image(xl + i, yt + j, 0) = 250;
        }
    }

}

void Simulation::render(Maze const* maze, const unsigned char* color)
{
    const unsigned char gray[] = {20, 20, 20 };

    int pixelScale = CELLWIDTH_MM / MMPERPIXEL;
    int postSizePixels = POSTWIDTH_MM / MMPERPIXEL;

    // Debug Grid
    for (int x = 0; x < image.width(); x += pixelScale/2)
    {
        image.draw_line(x, 0, x, image.height() - 1, gray);
    }
    for (int y = 0; y < image.height(); y += pixelScale/2)
    {
        image.draw_line(0, y, image.width() - 1, y, gray);
    }

    int size = maze->getSize();

    for (int x = 0; x < size; ++x)
    {
        for (int y = size - 1; y >=0; y--)
        {
            render(maze, x, y, color);
        }
    }

    // draw South wall
    int xl = 0;
    int xr = MAZESIZE * pixelScale;
    int y = MAZESIZE * pixelScale;

    for (int i = 0; i < postSizePixels; ++i)
        image.draw_line(xl, y + i, xr, y + i, color);

    // draw East wall
    int yb = MAZESIZE*pixelScale;
    int yt = 0;
    int x = MAZESIZE*pixelScale;

    for (int i = 0; i < postSizePixels; ++i)
        image.draw_line(x + i, yt, x + i, yb, color);

}

void Simulation::render(Mouse const* mouse)
{
    int mouseWidthPixels = MOUSEWIDTH_MM / MMPERPIXEL;
    int pixelScale = CELLWIDTH_MM / MMPERPIXEL;

    // first erase the pixels from the previous render
    int xc = pixelScale*xprev + pixelScale/2 - mouseWidthPixels/2  + 1;
    int yc = pixelScale*(MAZESIZE - 1 - yprev) + pixelScale/2 - mouseWidthPixels/2  + 1;
    // ToDO: check block erase
    for (int i = 0; i < mouseWidthPixels; ++i)
    {
        for (int j = 0; j < mouseWidthPixels; ++j)
        {
            image(xc + i, yc + j, 2) = 0;
            image(xc + i, yc + j, 1) = 0;
            image(xc + i, yc + j, 0) = 0;
        }
    }

    // Now start drawing the mouse for this render
    // (xc, yc) is the topleft pixel of the 3xx mouse image
    xc = pixelScale*mouse->getX() + pixelScale/2 - mouseWidthPixels/2  + 1;
    yc = pixelScale*(MAZESIZE - 1 - mouse->getY()) + pixelScale/2 - mouseWidthPixels/2  + 1;

    cimg_library::CImg<unsigned char> mouseImage;
    
    switch( mouse->getTheta())
    {
    case 0:
        mouseImage = orientedMouseArt[0];
        break;
    case 90:
        mouseImage = orientedMouseArt[3];
        break;
    case 180:
        mouseImage = orientedMouseArt[2];
        break;
    case 270:
        mouseImage = orientedMouseArt[1];
        break;
    }

    std::cout << mouseImage.height() << " mouse img " << mouseImage.width() << std::endl;
    std::cout << "MWP " << mouseWidthPixels << std::endl;
    
    for (int i = 0; i < mouseWidthPixels; ++i)
    {
        for (int j = 0; j < mouseWidthPixels; ++j)
        {
            image(xc + i, yc + j, 0) = mouseImage(i, j, 0);
            image(xc + i, yc + j, 1) = mouseImage(i, j, 1);
            image(xc + i, yc + j, 2) = mouseImage(i, j, 2);
        }
    }
    /*
    switch(mouse->getTheta())
    {
    case 0:
        image(xc + 2, yc + 1, 1) = 250;
        break;
    case 90:
        image(xc + 1, yc, 1) = 250;
        break;
    case 180:
        image(xc, yc + 1, 1) = 250;
        break;
    case 270:
        image(xc + 1, yc + 2, 1) = 250;
        break;
        }*/

    xprev = mouse->getX();
    yprev = mouse->getY();
}

void Simulation::readMouseArt(std::string const& fileName)
{
    cimg_library::CImg<unsigned char> img(fileName.c_str()) ;
    std::cout << img.height() << " img " << img.width() << std::endl;
    
    for (int i = 0; i < 4; ++i)
    {
        orientedMouseArt.push_back(img.get_rotate(90*i));
    }

    orientedMouseArt[0].save_bmp("0.bmp");
    orientedMouseArt[1].save_bmp("1.bmp");
    orientedMouseArt[2].save_bmp("2.bmp");


            
}


void Simulation::saveBMP(std::string& fileName)
{
    image.save_bmp(fileName.c_str());
}

void Simulation::saveBMP()
{
    char buff[120];
    snprintf(buff, sizeof(buff), "%05d", Simulation::frameNumber);
    std::string fileName = buff;
    image.save_bmp( (fileName + ".bmp").c_str());
    Simulation::frameNumber++;
}

    


void Simulation::scaleAndDisplay()
{
    
    image.display(display);
}
