#pragma once
#include <vector>
#include <Grid.hpp>

class World
{
private:
    int length; // Number of Rows, y-Dimension
    int width;  // Number of columns, x-Dimension
    Grid *gridMain;
    Grid *gridBuffer;
    int countNeighbours(int, int);

public:
    World(int, int);
    int getLength();
    int getWidth();
    void setCellAlive(int, int);
    void setCellDead(int, int);
    void printMain();
    void computeNextGeneration();
    bool getCellVital(int, int);
    void clear();
    void printSize();
};