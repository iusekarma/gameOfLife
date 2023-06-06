#include <iostream>
#include <World.hpp>
#include <Grid.hpp>

World::World(int length, int width) : length(length), width(width)
{
    gridMain = new Grid(length, width);
    gridBuffer = new Grid(length, width);
}

int World::getLength()
{
    return this->length;
}

int World::getWidth()
{
    return this->width;
}

void World::setCellAlive(int row, int column)
{
    this->gridMain->set(row, column);
}

void World::setCellDead(int row, int column)
{
    this->gridMain->reset(row, column);
}

void World::printMain()
{
    gridMain->printGrid();
}

int World::countNeighbours(int row, int column)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if ((i == 0) && (j == 0))
                continue;

            count += this->gridMain->get(row + i, column + j);
        }
    }
    return count;
}

void World::computeNextGeneration()
{
    for (int i = 0; i < this->length; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            int neighbours = this->countNeighbours(i, j);
            if (neighbours < 2)
            {
                gridBuffer->reset(i, j);
            }
            else if (neighbours == 2)
            {
                if (gridMain->get(i, j))
                {
                    gridBuffer->set(i, j);
                }
                else
                {
                    gridBuffer->reset(i, j);
                }
            }
            else if (neighbours == 3)
            {
                gridBuffer->set(i, j);
            }
            else if (neighbours > 3)
            {
                gridBuffer->reset(i, j);
            }
        }
    }
    gridMain->array = gridBuffer->array;
}

bool World::getCellVital(int row, int column)
{
    return gridMain->get(row, column);
}

void World::clear()
{
    for (int i = 0; i < this->getLength(); i++)
    {
        for (int j = 0; j < this->getWidth(); j++)
        {
            this->gridMain->reset(i, j);
        }
    }
}

void World::printSize(){
    std::cout << gridMain->array.size() << std::endl;
}