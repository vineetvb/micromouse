
#include "algorithm.h"
#include <iomanip>
#include "math_helpers.h"

CommandI Algorithm::getCommand(int xD, int yD)
{
    int xS = mouse->getX();
    int yS = mouse->getY();
    float thetaS = static_cast<float>(mouse->getTheta()) * toRadians;
    float ax = xD - xS, ay = yD - yS;

    // this norm is valid only for cardinal axis movements
    float norm = std::max( std::abs(ax), std::abs(ay) );
    ax /= norm;
    ay /= norm;

    float bx = std::cos(thetaS), by = std::sin(thetaS);

    float cval = ax * by - ay * bx; // cross product
    float dval = ax * bx + ay * by; // dot product

    float rotationAngle = std::acos(dval);
    float sense = -1; // default is anticlockwise
    if(cval > 0)
    {
        sense = 1;
    }
     rotationAngle *= sense;

     int steps = static_cast<int>(std::round(norm));
     int rotDegrees = static_cast<int>(std::round(rotationAngle * toDegrees));

     return CommandI(rotDegrees, steps);
}


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
    std::fill(visited.begin(), visited.end(), 0);
    std::queue<MazeNode> q;
    MazeNode goal(xGoal, yGoal, 0);
    q.push(goal);

    while(!q.empty())
    {
        MazeNode n = q.front(); q.pop();
        visited[n.y * size + n.x] = 1;
        
        bool nbrFound = false;
        // e is the explored neighbor that is pushed to the queue if
        // it is accessible
        // Top Neighbor is accesible, and not visited
        if (!maze->getUpWall(n.x, n.y) && visited[(n.y + 1) * size + n.x]==0)
        {
            MazeNode e(n.x, n.y + 1, n.val + 1);
            updateMazeNode(e, n, q);
            nbrFound = true;
        }

        // Left Neighbor is accesible, and not visited
        if (!maze->getLeftWall(n.x, n.y) && visited[n.y * size + (n.x - 1)]==0)
        {
            MazeNode e(n.x - 1, n.y, n.val + 1);
            updateMazeNode(e, n, q);
            nbrFound = true;
        }

        // Bottom Neighbor is accesible, and not visited
        if (!maze->getDownWall(n.x, n.y) && visited[(n.y - 1) * size + n.x]==0)
        {
            MazeNode e(n.x, n.y - 1, n.val + 1);
            updateMazeNode(e, n, q);
            nbrFound = true;
        }

        // Right Neighbor is accesible, and not visited
        if (!maze->getRightWall(n.x, n.y) && visited[n.y * size + (n.x + 1)]==0)
        {
            MazeNode e(n.x + 1, n.y, n.val + 1);
            updateMazeNode(e, n, q);
            nbrFound = true;
        }

        if(nbrFound==false)
        {
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

void FloodFillExplorationAlgorithm::backtrack(std::vector<MazeNode>& path)
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
        // Left neighbor is 1 step away, and accesible
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
    //show();
    std::vector<MazeNode> path;
    backtrack(path);
    return getCommand(path[1].x, path[1].y);
}

