#include "mouse.h"
#include "sensor.h"
#include <thread>

float deg2rad(int deg)
{
    return M_PI * (static_cast<float>(deg) / 180.0);
}

// Starting Position of the mouse is at (0,0) facing North/UP
Mouse::Mouse(void): cx(0), cy(0), ctheta(90)
{
    updateTf();
    internalMaze = new Maze(16);
    internalMaze->mouse = this;
    internalMaze->makeBoundaryWalls();

    // Add three sensors
    Sensor frontSensor(0,0,0);
    Sensor leftSensor(0,0,90);
    Sensor rightSensor(0,0,-90);

    addSensor(&frontSensor);
    addSensor(&leftSensor);
    addSensor(&rightSensor);
}

void Mouse::addSensor(Sensor* sensor)
{
    sensor->mouse = this;
    sensors.push_back(*sensor);
    sensorOutputs.push_back(0);
}

void Mouse::show()
{
    std::string arrow;
    switch(ctheta)
    {
        case 0:
            arrow = " > ";
            break;

        case 90:
            arrow = " ^ ";
            break;

        case 180:
            arrow = " < ";
            break;

        case 270:
            arrow = " v ";
            break;
    }

    std::cout << "Mouse: ( " << cx << " " << cy << " " << ") " << arrow << std::endl;
    std::cout << "Sensors: FLR " << int(sensorOutputs[0])
                        << " " << int(sensorOutputs[1])
                        << " " << int(sensorOutputs[2]) << std::endl
                        << "```````````" << std::endl;
}

void Mouse::turn(int theta)
{
    ctheta += theta;
    ctheta %= 360;
    updateTf();
};


bool Mouse::advance(float theta, float x, Maze const* refMaze)
{
    /* Note that the turn is done before the forward movement.
       e.g. 1, 90 implies, turn by 90 and then advance by 1 unit.
*/
    int xi = static_cast<int>(x);
    int cti = static_cast<int>(theta);

    ctheta += cti;
    ctheta %= 360;
    float costht = std::cos(deg2rad(ctheta));
    float sintht = std::sin(deg2rad(ctheta));

    int cxnew = xi*costht + cx;
    int cynew = xi*sintht + cy;

    bool success = false;

    // Collision Detection
    if (cy == cynew)
    {
        // horizontal movement of mouse
        if (cxnew > cx)
        {
            // moving rightward, check right wall of current cell
            success = !refMaze->getRightWall(cx, cy);
        }
        else
        {
            // leftward
            success = !refMaze->getLeftWall(cx, cy);
        }
    }
    else
    {
        // vertical movement of mouse
        if( cynew > cy)
        {
            // going up
            success = !refMaze->getUpWall(cx, cy);
        }
        else
        {
            // going down
            success = !refMaze->getDownWall(cx, cy);
        }
    }

    if (success)
    {
        cx = cxnew;
        cy = cynew;
    }

    return success;
}

/*
Command object specifies two values to update
(cx', theta'). These are the realtive values in the robot
frame of reference.
*/
bool Mouse::executeCommand(CommandI const* command, Maze const * refMaze)
{
    return this->advance(command->theta, command->x, refMaze);
}


void Mouse::updateTf()
{
    Tf[0] = std::cos(deg2rad(ctheta));
    Tf[1] = -std::sin(deg2rad(ctheta));
    Tf[2] = std::sin(deg2rad(ctheta));
    Tf[3] = std::cos(deg2rad(ctheta));
}



// populates the sensor readings array with the latest data
void Mouse::readSensors(Maze const* refMaze)
{
    for (int i = 0; i < sensors.size(); ++i)
    {
        sensorOutputs[i] = sensors[i].readReferenceMaze(refMaze);
    }
}

void Mouse::setAlgorithm(Algorithm * algo)
{
    algorithm = algo;
    static_cast<RandomExplorerAlgorithm *>(algorithm)->mouse = this;
}


// runs algorithm in infinite loop
void Mouse::start(Maze const* refMaze, Simulation * sim)
{
    sim->render(refMaze);
    while (!sim->display.is_closed())
    {
        show();

        readSensors(refMaze);

        const CommandI c = algorithm->process();
        this->executeCommand(&c, refMaze);

        if (sim)
        {
            sim->render(refMaze);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
