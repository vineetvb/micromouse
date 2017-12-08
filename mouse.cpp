#include "mouse.h"
#include "sensor.h"

float deg2rad(int deg)
{
    return M_PI * (static_cast<float>(deg) / 180.0);
}

// Starting Position of the mouse is at (0,0) facing North/UP
Mouse::
Mouse(void): cx(0), cy(0), ctheta(90)
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

void
Mouse::
addSensor(Sensor* sensor)
{
    sensor->mouse = this;
    sensors.push_back(*sensor);
    sensorOutputs.push_back(0);
}

void
Mouse::
show()
{
    std::cout << "Mouse: ( " << cx << " " << cy << " " << ctheta << ")" << std::endl;
    std::cout << "Sensors: FLR " << int(sensorOutputs[0])
                        << " " << int(sensorOutputs[1])
                        << " " << int(sensorOutputs[2]) << std::endl
                        << "```````````" << std::endl;
}

void
Mouse::
turn(int theta)
{
    ctheta += theta;
    ctheta = ctheta % 360;
    updateTf();
};


// advance forward by 1 position
void
Mouse::
advance(void)
{
    cx = Tf[0]*1 + Tf[1]*0 + cx;
    cy = Tf[2]*1 + Tf[3]*0 + cy;
}

void
Mouse::
updateTf()
{
    Tf[0] = std::cos(deg2rad(ctheta));
    Tf[1] = -std::sin(deg2rad(ctheta));
    Tf[2] = std::sin(deg2rad(ctheta));
    Tf[3] = std::cos(deg2rad(ctheta));
}

// populates the sensor readings array with the latest data
void
Mouse::
readSensors(Maze const* refMaze)
{
    for (int i = 0; i < sensors.size(); ++i)
    {
        sensorOutputs[i] = sensors[i].readReferenceMaze(refMaze);
    }
}
