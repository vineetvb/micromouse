
#include "algorithm.h"

const CommandI RandomExplorerAlgorithm::process()
{
    // default command
    CommandI c(0, 1);

    const std::vector<bool> sensors = mouse->getSensorState();

    int i = dis(gen);

    if (sensors[0] == true)
    {
        if (i < 5)
            c = CommandI(90, 0);
        else
            c = CommandI(-90, 0);
    } else {
        if (sensors[1] == false && i == 0)
        {
            c = CommandI(90, 0);
        }
        if (sensors[2] == false && i == 0)
        {
            c = CommandI(-90, 0);
        }
    }

    int xpos = mouse->getX();
    int ypos = mouse->getY();

    if (xpos == 7 && ypos ==7)
    {
        c = CommandI(0, 0);
    }
    return c;
}
