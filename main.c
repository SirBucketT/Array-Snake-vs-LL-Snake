#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include <time.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define CELL_SIZE     20

// Snake settings
#define SNAKE_MAX_LENGTH  1000
#define INITIAL_LENGTH    5
#define GAME_SPEED        10

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

struct GameState {
    Vector2 snakePositions[SNAKE_MAX_LENGTH];
    int snakeLength;
    Direction currentDirection;
    Vector2 foodPosition;

    bool gameOver;
    bool gamePaused;
    int framesCounter;
} gameState;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

void GameSetup(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake.. Snake.. SNAKE!");

    // Seed the random number generator:
    srand( time(NULL) );

    gameState.gameOver = false;
    gameState.gamePaused = false;
    gameState.framesCounter = 0;

    gameState.snakeLength = INITIAL_LENGTH;
    gameState.currentDirection = DIR_RIGHT;

    // Position the snake in the middle of the screen, in "grid" coordinates
    int centerX = (SCREEN_WIDTH / CELL_SIZE) / 2;
    int centerY = (SCREEN_HEIGHT / CELL_SIZE) / 2;

    // Initialize the snake segments
    for (int i = 0; i < gameState.snakeLength; i++) {
        // Each segment is placed one cell to the left of the previous (horizontal snake)
        gameState.snakePositions[i].x = centerX - i;
        gameState.snakePositions[i].y = centerY;
    }

    // Create an initial food location
    gameState.foodPosition.x = rand() % (SCREEN_WIDTH  / CELL_SIZE);
    gameState.foodPosition.y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
}

void ProcessInput(void){

    if (gameState.gameOver && IsKeyPressed(KEY_R)){
        GameSetup();
        return;
    }


    if (IsKeyPressed(KEY_P)){
        gameState.gamePaused = !gameState.gamePaused;
    }

    //checks input
    if (!gameState.gamePaused && !gameState.gameOver) {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) && gameState.currentDirection != DIR_UP) {
            gameState.currentDirection = DIR_UP;
        }
        if (IsKeyPressed(KEY_DOWN)|| IsKeyPressed(KEY_S) && gameState.currentDirection != DIR_DOWN) {
            gameState.currentDirection = DIR_DOWN;
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) && gameState.currentDirection != DIR_LEFT) {
            gameState.currentDirection = DIR_LEFT;
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) && gameState.currentDirection != DIR_RIGHT) {
            gameState.currentDirection = DIR_RIGHT;
        }
    }

    //snake movement
    switch (gameState.currentDirection) {
        case DIR_UP:
            gameState.snakePositions[0].y -= GAME_SPEED;
        break;
        case DIR_DOWN:
            gameState.snakePositions[0].y += GAME_SPEED;
        case DIR_LEFT:
            gameState.snakePositions[0].x -= GAME_SPEED;
        break;
        case DIR_RIGHT:
            gameState.snakePositions[0].x += GAME_SPEED;
        break;
    }

    for (int i = gameState.snakeLength - 1; i >= 0; i--) {
        gameState.snakePositions[i] = gameState.snakePositions[i + 1];
    }
}



int main(void) {

    GameSetup();

    while (!WindowShouldClose()){
        DrawFPS(SCREEN_WIDTH - SCREEN_WIDTH + 10, SCREEN_HEIGHT - SCREEN_HEIGHT + 10);
        ProcessInput();
          //  UpdateGame();
            //RenderGame();
        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }
    CloseWindow();
    //CloseGame();
    return 0;
}