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

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

snakeData() {
    Vector2 snake[SNAKE_MAX_LENGTH];
    int snakeLength = INITIAL_LENGTH;
    Direction currentDirection = DIR_RIGHT;

    int startX = SCREEN_WIDTH / 2 / CELL_SIZE;
    int startY = SCREEN_HEIGHT / 2 / CELL_SIZE;
    for (int i = 0; i < snakeLength; i++) {
        snake[i].x = startX - i;
        snake[i].y = startY;
    }
}

food() {
    Vector2 food;
    food.x = rand() % (SCREEN_WIDTH / CELL_SIZE);
    food.y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
}

int main(void) {s
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake.. Snake.. SNAKE!");
    SetTargetFPS(60);

    bool gameOver = false;
    bool gamePaused = false;

    int framesCounter = 0;

    srand((unsigned int)time(NULL));

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}