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

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake.. Snake.. SNAKE!");
    SetTargetFPS(60);

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}