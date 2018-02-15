#include "mouse.h"
#include "sensor.h"

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


bool Mouse::advance(Maze const* refMaze)
{
    int cxnew = Tf[0]*1 + Tf[1]*0 + cx;
    int cynew = Tf[2]*1 + Tf[3]*0 + cy;

    bool success = false;

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
