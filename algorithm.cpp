
#include "algorithm.h"
#include <iomanip>

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

FloodFillExplorationAlgorithm::FloodFillExplorationAlgorithm()
{
}

void FloodFillExplorationAlgorithm::init()
{
    // Algorithm starts with whatever the mouse has explored so far
    maze = mouse->getInternalMaze();
    size = maze->getSize();

    visited = std::vector<char>(size*size, 0);
    floodVal = std::vector<int>(size*size, 0);
    xGoal = (size - 1)/2;
    yGoal = (size - 1)/2;
}


void FloodFillExplorationAlgorithm::updateMazeNode(MazeNode& e, MazeNode&n, std::queue<MazeNode>& q)
{
    visited[e.y * size + e.x] = 1;
    q.push(e);
    floodVal[e.y * size + e.x] = n.val + 1;
}


void FloodFillExplorationAlgorithm::flood()
{

    std::queue<MazeNode> q;
    MazeNode goal(xGoal, yGoal, 0);
    q.push(goal);

    while(!q.empty())
    {

        MazeNode n = q.front(); q.pop();


        visited[n.y * size + n.x] = 1;

        // e is the explored node

        // Top Neighbor is accesible, and not visited
        if (!maze->getUpWall(n.x, n.y) && visited[(n.y + 1) * size + n.x]==0)
        {
            MazeNode e(n.x, n.y + 1, n.val + 1);
            updateMazeNode(e, n, q);
        }

        // Left Neighbor is accesible, and not visited
        if (!maze->getLeftWall(n.x, n.y) && visited[n.y * size + (n.x - 1)]==0)
        {
            MazeNode e(n.x - 1, n.y, n.val + 1);
            updateMazeNode(e, n, q);
        }

        // Bottom Neighbor is accesible, and not visited
        if (!maze->getDownWall(n.x, n.y) && visited[(n.y - 1) * size + n.x]==0)
        {
            MazeNode e(n.x, n.y - 1, n.val + 1);
            updateMazeNode(e, n, q);
        }

        // Right Neighbor is accesible, and not visited
        if (!maze->getRightWall(n.x, n.y) && visited[n.y * size + (n.x + 1)]==0)
        {
            MazeNode e(n.x + 1, n.y, n.val + 1);
            updateMazeNode(e, n, q);
        }
    }

}

void FloodFillExplorationAlgorithm::show()
{
    using namespace std;

    for(int y = size - 1; y >=0; y--)
    {
        for (int x = 0; x < size; ++x)
        {
            cout << std::setw(3) << floodVal[y * size + x]  << " | " ;
        }
        cout << endl;
    }
    cout << endl;
}

void FloodFillExplorationAlgorithm::backtrack(vector<MazeNode>& path)
{
    int xC = mouse->getX(), yC = mouse->getY();
    int xN, yN;

    while(true)
    {
        path.push_back(MazeNode(xC, yC, floodVal[yC*size + xC]) );

        if(xC==xGoal && yC==yGoal)
        {
            break;
        }

        xN = xC; yN = yC + 1;
        // Top neighbor is 1 step away, and accesible
        if ( !maze->getUpWall(xC, yC)
              && (floodVal[yC*size + xC] - floodVal[yN*size + xN]  == 1 )
            )
        {
            xC = xN;
            yC = yN;
            continue;
        }

        xN = xC - 1; yN = yC;
        // Leftp neighbor is 1 step away, and accesible
        if ( !maze->getLeftWall(xC, yC)
             && (floodVal[yC*size + xC] - floodVal[yN*size + xN]  == 1 )
           )
        {
            xC = xN;
            yC = yN;
            continue;
        }

        xN = xC; yN = yC - 1;
        // Bottom neighbor is 1 step away, and accesible
        if ( !maze->getDownWall(xC, yC)
             && (floodVal[yC*size + xC] - floodVal[yN*size + xN]  == 1 )
            )
        {
            xC = xN;
            yC = yN;
            continue;
        }

        xN = xC + 1; yN = yC;
        // Right neighbor is 1 step away, and accesible
        if ( !maze->getRightWall(xC, yC)
             && (floodVal[yC*size + xC] - floodVal[yN*size + xN]  == 1 )
            )
        {
            xC = xN;
            yC = yN;
            continue;
        }
    }
}

const CommandI FloodFillExplorationAlgorithm::process()
{
    flood();
    show();
    vector<MazeNode> path;
    backtrack(path);
    return CommandI(0, 0);
}
