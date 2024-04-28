#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void InitGrid();
    void PrintGrid();
    void Draw();
    bool IsCellOffScreen(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();

    
private:

    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowsDown(int row, int numRow);
   

public:
    int grid[20][10];   

private:
    int numRows;
    int numColumns;
    int cellSize;
    std::vector<Color> colors;
};