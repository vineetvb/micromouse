#ifndef MOUSE_H_
#define MOUSE_H_

#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include "maze.h"
#include "sensor.h"
#include "command.h"
#include "algorithm.h"
#include "simulation.h"

#define _USE_MATH_DEFINES

float deg2rad(int deg);

class Maze;
class Sensor;
class Simulation;
class Algorithm;

class Mouse
{
private:
    // internal representation of explored maze
    Maze* internalMaze;

    // Algorithm used to move in the maze
    Algorithm * algorithm;

    void readWalls();

    void turn(int theta);

    void updateTf();

    /**
       Attempt moving forward.
       Args:
        refMaze: ptr to maze in which to move forward.
       Returns false on collision with refMaze.
    */
    bool advance(Maze const* refMaze);

    // Intended to be private. To be used with the appropriate Command interface
    bool advance(float theta, float x, Maze const* refMaze);

    // writes an individual sensor's output to the internal maze
    void writeSensorData(bool data, int theta);

    // Reads current sensorOutputs and updates the internal rep of maze
    void updateInternalMaze();

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

    const std::vector<bool> getSensorState() const {return sensorOutputs;};

    Maze * getInternalMaze() const { return internalMaze; };

    int getX() const {return cx;}
    int getY() const {return cy;}
    int getTheta() const {
      int theta = (ctheta + 360) % 360;
	return theta;}

    void show();

    void start(Maze const* refMaze, Simulation * sim = nullptr);

    void setAlgorithm(Algorithm * algorithm);
};

#endif
