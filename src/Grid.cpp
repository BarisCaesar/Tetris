#include "Grid.h"
#include "Colors.h"
#include <iostream>


Grid::Grid()
{
    numRows = 20;
    numColumns = 10;
    cellSize = 30;
    InitGrid();
    colors = GetCellColors();

}

void Grid::InitGrid()
{
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::PrintGrid()
{
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            std::cout << grid[i][j] << " ";
        }

        std::cout <<  std::endl;
    }

}



void Grid::Draw()
{

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            int cellValue = grid[i][j];
            DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }

    }   
}

bool Grid::IsCellOffScreen(int row, int column)
{
    if(row >= 0 && row < numRows && column >= 0 && column < numColumns)
    {
        return false;
    }
    return true;

}

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column] != 0)
    {
        return false;
    }
    return true;

}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int i = numRows - 1; i >= 0; i--)
    {
        if(IsRowFull(i))
        {
            ClearRow(i);
            completed++;
        }
        else if(completed > 0)
        {
            MoveRowsDown(i, completed);
        }
    }

    return completed;
}

bool Grid::IsRowFull(int row)
{
    for(int i = 0; i < numColumns; i++)
    {
        if(grid[row][i] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int i = 0; i < numColumns; i++)
    {
        grid[row][i] = 0;
    }
}

void Grid::MoveRowsDown(int row, int numRow)
{
    for(int i = 0; i < numColumns; i++)
    {
        grid[row + numRow][i] = grid[row][i];
        grid[row][i] = 0;
    }   
}
