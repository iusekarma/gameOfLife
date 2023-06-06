#include <Grid.hpp>
#include <iostream>

Grid::Grid(int rows, int columns) : totalRows(rows), totalColumns(columns)
{
    for (int i = 0; i < this->totalRows; i++)
    {
        this->array.push_back(std::vector<bool>(this->totalColumns, 0));
    }
}

bool Grid::get(int row, int column)
{
    row = (this->totalRows + row) % this->totalRows;
    column = (this->totalColumns + column) % this->totalColumns;
    return this->array[row][column];
}

void Grid::set(int row, int column)
{
    row = (this->totalRows + row) % this->totalRows;
    column = (this->totalColumns + column) % this->totalColumns;
    this->array[row][column] = 1;
}

void Grid::reset(int row, int column)
{
    row = (this->totalRows + row) % this->totalRows;
    column = (this->totalColumns + column) % this->totalColumns;
    this->array[row][column] = 0;
}

int Grid::getRows()
{
    return this->totalRows;
}

int Grid::getColumns()
{
    return this->totalColumns;
}

void Grid::printGrid()
{
    for (int i = 0; i < this->totalRows; i++)
    {
        for (int j = 0; j < this->totalColumns; j++)
        {
            std::cout << this->get(i, j);
        }
        std::cout << std::endl;
    }
}
