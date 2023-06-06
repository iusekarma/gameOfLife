#pragma once
#include <vector>

class Grid
{
private:
    int totalRows;
    int totalColumns;

public:
    Grid(int, int);
    bool get(int, int);
    void set(int, int);
    void reset(int, int);
    int getRows();
    int getColumns();
    void printGrid();
    std::vector<std::vector<bool>> array;
};
