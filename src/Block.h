#pragma once
#include<vector>
#include <raylib.h>
#include<map>
#include "Position.h"


class Block
{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int row, int column);
    void Rotate();
    void UndoRotation();
    std::vector<Position> GetCellPositions();
private:


public:
    int id;
    std::map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;

};