#pragma once
#include "Grid.h"
#include "Blocks.h"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveDown();

private:
    void MoveLeft();
    void MoveRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool IsBlockOffScreen();
    void RotateBlock();
    void LockBlock();
    bool DoesBlockFit();
    void Reset();
    void UpdateScore(int linesCleared, int numMoveDown);

public:
    bool isGameOver;
    int score;

private:
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;

};