#include "Block.h"
#include "Colors.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for(Position position : tiles)
    {
        DrawRectangle(position.column * cellSize + offsetX, position.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int row, int column)
{
    rowOffset += row;
    columnOffset += column;
}

void Block::Rotate()
{
    if((int)cells.size() == 0)
    {
        rotationState = 0;
    }
    else
    {
        rotationState = (rotationState + 1) % (int)cells.size();
    }

}

void Block::UndoRotation()
{
    if((int)cells.size() == 0)
    {
        rotationState = 0;
    }
    else
    {
        rotationState = (rotationState > 0) ? rotationState - 1 : (int)cells.size() - 1;
    }   

}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;

    for(Position position : tiles)
    {
        Position newPos = Position(position.row + rowOffset, position.column + columnOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;

} 