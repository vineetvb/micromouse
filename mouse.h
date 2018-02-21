#ifndef MOUSE_H_
#define MOUSE_H_

#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include "maze.h"
#include "sensor.h"
#include "command.h"

#define _USE_MATH_DEFINES

float deg2rad(int deg);

class Maze;
class Sensor;

class Mouse
{
private:
    // internal representation of explored maze
    Maze* internalMaze;

    void readWalls();

    void turn(int theta);

    void updateTf();

    /**
       Attempt moving forward.
       Returns false on collision with refMaze.
    */
    bool advance(Maze const* refMaze);

    // Intended to be private. To be used with the appropriate Command interface
    bool advance(float theta, float x, Maze const* refMaze);


    //current x,y, theta position
    // This mouse only supports integer coords
    int cx, cy, ctheta;

    std::array<int, 4> Tf;

    // Sensors on this mouse
    std::vector<Sensor> sensors;
    std::vector<bool> sensorOutputs;

 public:
    Mouse(void);

    bool executeCommand(CommandI const* command, Maze const * refMaze);
    void addSensor(Sensor * sensor);
    void readSensors(Maze const* refMaze);

    int getX() const {return cx;}
    int getY() const {return cy;}
    int getTheta() const {return ctheta;}

    void show();

};

#endif
