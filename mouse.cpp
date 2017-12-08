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

    sensors.push_back(frontSensor);
    sensors.push_back(leftSensor);
    sensors.push_back(rightSensor);

    // initial sensor ouputs
    sensorOutputs.push_back(0);
    sensorOutputs.push_back(0);
    sensorOutputs.push_back(0);
}

// advance forward by 1 position
void
Mouse::
advance(void)
{
    cx = Tf[0]*1 + Tf[1]*0 + cx;
    cy = Tf[2]*1 + Tf[3]*0 + cy;

    // update position of sensors
    for (auto& sen : sensors)
    {
        sen.cx = cx;
        sen.cy = cy;
        sen.ctheta += ctheta;
        sen.ctheta = sen.ctheta % 360;
    }
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





