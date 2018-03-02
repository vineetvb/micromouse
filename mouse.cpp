#include "mouse.h"
#include "sensor.h"
#include <thread>

//ToDo: check std cmath methods
float deg2rad(int deg)
{
    return M_PI * (static_cast<float>(deg) / 180.0);
}

// Starting Position of the mouse is at (0,0) facing North/UP
Mouse::Mouse(void): cx(0), cy(0), ctheta(90)
{
    updateTf();
    internalMaze = new Maze(MAZESIZE);
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
    ctheta += (theta + 360);
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

    ctheta += (cti + 360);
    ctheta %= 360;
    float costht = std::cos(deg2rad(ctheta));
    float sintht = std::sin(deg2rad(ctheta));
    float cxnewf = xi*costht + cx;
    float cynewf = xi*sintht + cy;
    int cxnew = static_cast<int>(std::round(cxnewf));
    int cynew = static_cast<int>(std::round(cynewf));

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
    algorithm->mouse = this;
    algorithm->init();
}

void Mouse::writeSensorData(bool data, int theta)
{
    // angle of the sensor relative to the maze
    int sensTheta = (ctheta + theta + 360) % 360;
    if(data)
    {
        if (sensTheta == 0) // facing RIGHT
        {
            internalMaze->setRightWall(cx, cy);
        }

        if (sensTheta == 90 ) // facing UP
        {
            internalMaze->setUpWall(cx, cy);
        }

        if (sensTheta == 180) // facing LEFT
        {
            internalMaze->setLeftWall(cx, cy);
        }

        if (sensTheta == 270) // facing DOWN
        {
            internalMaze->setDownWall(cx, cy);
        }
    }


}

void Mouse::updateInternalMaze()
{
    // angles corresponding to F,L,R
    int angles[] = {0, 90, -90};
    for (int i = 0; i < sensorOutputs.size(); ++i)
    {
        writeSensorData(sensorOutputs[i], angles[i]);
    }
}


#include <iomanip>
// runs algorithm in infinite loop
void Mouse::start(Maze const* refMaze, Simulation * sim)
{
    const unsigned char red[] = {200, 20, 20 };
    const unsigned char green[] = {100, 120, 20 };
    using namespace std;

    // Render the maze once
    if (sim)
    {
        sim->render(refMaze, red);
        sim->scaleAndDisplay();
    }

    // while the mouse is moving keep updating the mouse position
    while (!sim->display.is_closed())
    {

        readSensors(refMaze);

        updateInternalMaze();

        const CommandI c = algorithm->process();

        this->executeCommand(&c, refMaze);

        if (sim)
        {
            sim->render(this);
            sim->render(internalMaze, green);
            sim->scaleAndDisplay();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
