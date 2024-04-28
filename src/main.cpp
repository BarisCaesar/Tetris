#include <raylib.h>
#include <iostream>
#include "Game.h"
#include "Colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

int main()
{
    const int screenWidth = 500;
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();

        if(EventTriggered(0.2))
        {
            game.MoveDown();
        }

        BeginDrawing();
        ClearBackground(black);

        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if(game.isGameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }
       
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, grey);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, grey);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}