
#include "algorithm.h"

const CommandI RandomExplorerAlgorithm::process()
{
    // default command
    CommandI c(0, 1);

    const std::vector<bool> sensors = mouse->getSensorState();

    if (sensors[0] == true)
    {
        c = CommandI(90, 0);
    }

    return c;
}
