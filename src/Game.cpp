#include "Game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    isGameOver = false;
    score = 0;
    InitAudioDevice();
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");

}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();

}

Block Game::GetRandomBlock()
{
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    if(nextBlock.id == 3)
    {
        nextBlock.Draw(255, 290);
    }
    else if(nextBlock.id == 4)
    {
        nextBlock.Draw(255, 280);
    }
    else
    {
        nextBlock.Draw(270, 270);
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if(isGameOver && keyPressed != 0)
    {
        isGameOver = false;
        Reset();
    }

    if(keyPressed == KEY_S)
    {
        MoveDown();

    }
    else if(keyPressed == KEY_A)
    {
        MoveLeft();
    }
    else if(keyPressed == KEY_D)
    {
        MoveRight();
    }
    else if(keyPressed == KEY_W)
    {
        RotateBlock();
    }
}


void Game::MoveLeft()
{
    if(isGameOver)
    {
        return;
    }
    currentBlock.Move(0, -1);
    if(IsBlockOffScreen() || !DoesBlockFit())
    {
        currentBlock.Move(0, 1);
    }
}

void Game::MoveRight()
{
    if(isGameOver)
    {
        return;
    }
    currentBlock.Move(0, 1);
    if(IsBlockOffScreen() || !DoesBlockFit())
    {
        currentBlock.Move(0, -1);
    }
}

void Game::MoveDown()
{
    if(isGameOver)
    {
        return;
    }
    currentBlock.Move(1, 0);
    if(IsBlockOffScreen() || !DoesBlockFit())
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
    else
    {
        UpdateScore(0, 1);
    }
}

bool Game::IsBlockOffScreen()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for(Position position : tiles)
    {
        if(grid.IsCellOffScreen(position.row, position.column))
        {
            return true;
        }
    }
    
    return false;
}

void Game::RotateBlock()
{
    if(isGameOver)
    {
        return;
    }
    currentBlock.Rotate();
    if(IsBlockOffScreen() || !DoesBlockFit())
    {
        currentBlock.UndoRotation();
    }
    else
    {
        PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position position : tiles)
    {
        grid.grid[position.row][position.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
    if(!DoesBlockFit())
    {
        isGameOver = true;
    }

    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
    }

    UpdateScore(rowsCleared, 0);
}

bool Game::DoesBlockFit()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position position : tiles)
    {
        if(!grid.IsCellEmpty(position.row, position.column))
        {
            return false;
        }
    }

    return true;

}

void Game::Reset()
{
    grid.InitGrid();
    blocks = GetAllBlocks();

    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

    score = 0;

}

void Game::UpdateScore(int linesCleared, int numMoveDown)
{
    if(linesCleared == 1)
    {
        score += 100;
    }
    else if(linesCleared == 2)
    {
        score += 300;
    }
    else if(linesCleared == 3)
    {
        score += 500;
    }

    score += numMoveDown;
}