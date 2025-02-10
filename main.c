#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"
#include <time.h>

#define SCREEN_WIDTH  1800
#define SCREEN_HEIGHT 800
#define CELL_SIZE     15

// Snake settings
#define SNAKE_MAX_LENGTH  1000
#define INITIAL_LENGTH    5
#define GAME_SPEED        1

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
    int score;
} gameState;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

void GameSetup(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake.. Snake.. SNAKE!");
    SetTargetFPS(35);

    srand(time(NULL));

    gameState.gameOver = false;
    gameState.gamePaused = false;
    gameState.framesCounter = 0;
    gameState.score = 0;

    gameState.snakeLength = INITIAL_LENGTH;
    gameState.currentDirection = DIR_RIGHT;

    int centerX = (SCREEN_WIDTH / CELL_SIZE) / 2;
    int centerY = (SCREEN_HEIGHT / CELL_SIZE) / 2;

    for (int i = 0; i < gameState.snakeLength; i++) {
        gameState.snakePositions[i].x = centerX - i;
        gameState.snakePositions[i].y = centerY;
    }

    //gameState.foodPosition.x = rand() % (SCREEN_WIDTH  / CELL_SIZE);
    //gameState.foodPosition.y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
}

// -----------------------------------------------------------------------
// Game input, movement logic & snake rendering
// -----------------------------------------------------------------------
void ProcessInput(void) {

    gameState.framesCounter += 1;

    if (gameState.gameOver && IsKeyPressed(KEY_R)) {
        GameSetup();
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        gameState.gamePaused = !gameState.gamePaused;
    }

    if (!gameState.gamePaused && !gameState.gameOver) {
        if ((IsKeyPressed(KEY_UP)   || IsKeyPressed(KEY_W)) && gameState.currentDirection != DIR_UP && gameState.currentDirection != DIR_DOWN) {
            gameState.currentDirection = DIR_UP;
        }
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && gameState.currentDirection != DIR_DOWN && gameState.currentDirection != DIR_UP) {
            gameState.currentDirection = DIR_DOWN;
        }
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && gameState.currentDirection != DIR_LEFT && gameState.currentDirection != DIR_RIGHT) {
            gameState.currentDirection = DIR_LEFT;
        }
        if ((IsKeyPressed(KEY_RIGHT)|| IsKeyPressed(KEY_D)) && gameState.currentDirection != DIR_RIGHT && gameState.currentDirection != DIR_LEFT) {
            gameState.currentDirection = DIR_RIGHT;
        }
    }

    switch (gameState.currentDirection) {
        case DIR_UP:
            gameState.snakePositions[0].y -= GAME_SPEED;
            break;
        case DIR_DOWN:
            gameState.snakePositions[0].y += GAME_SPEED;
            break;
        case DIR_LEFT:
            gameState.snakePositions[0].x -= GAME_SPEED;
            break;
        case DIR_RIGHT:
            gameState.snakePositions[0].x += GAME_SPEED;
            break;
    }

    for (int i = 0; i < gameState.snakeLength; i++) {
        if (i == 0) {
            DrawRectangle(
                (int)gameState.snakePositions[i].x * CELL_SIZE,
                (int)gameState.snakePositions[i].y * CELL_SIZE,
                CELL_SIZE, CELL_SIZE,
                GREEN
            );
        } else {
            DrawRectangle(
                (int)gameState.snakePositions[i].x * CELL_SIZE,
                (int)gameState.snakePositions[i].y * CELL_SIZE,
                CELL_SIZE, CELL_SIZE,
                BLACK
            );
        }
    }

    if (gameState.framesCounter >= GAME_SPEED) {
        gameState.framesCounter = 0;
        for (int j = gameState.snakeLength - 1; j > 0; j--) {
            gameState.snakePositions[j] = gameState.snakePositions[j - 1];
        }
    }
    if (gameState.snakePositions[0].x >= SCREEN_WIDTH || gameState.snakePositions[0].y >= SCREEN_HEIGHT) {
        gameState.gameOver = true;
    }
}

void FoodUpdate(void) {
    gameState.foodPosition.x = rand() % (SCREEN_WIDTH  / CELL_SIZE);
    gameState.foodPosition.y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
}

// -----------------------------------------------------------------------
// Food spawner, score manager & food position updater
// -----------------------------------------------------------------------

void Food(void) {

    DrawText(TextFormat("Score %d", gameState.score),
          SCREEN_WIDTH / 2, +20,
          25, BLACK);

    bool isEaten = false;

    if (isEaten != true) {
        DrawRectangle(
        (int)gameState.foodPosition.x * CELL_SIZE,
        (int)gameState.foodPosition.y * CELL_SIZE,
        CELL_SIZE, CELL_SIZE,
        RED
        );
    }
    if (gameState.snakePositions[0].x != gameState.foodPosition.x && gameState.snakePositions[0].y != gameState.foodPosition.y) {
        isEaten = true;
    } else if (gameState.snakePositions[0].x == gameState.foodPosition.x && gameState.snakePositions[0].y == gameState.foodPosition.y) {
        gameState.score++;
        gameState.snakeLength++;
        FoodUpdate();
    }
    if (gameState.snakePositions[0].x < 0 || gameState.snakePositions[0].x >= SCREEN_WIDTH / CELL_SIZE || gameState.snakePositions[0].y < 0 || gameState.snakePositions[0].y >= SCREEN_HEIGHT / CELL_SIZE) {
        gameState.gameOver = true;
     }
}

void GameOverCheck(void) {
    if (gameState.gameOver) {
        DrawText("Game Over", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 30, BLACK);
    }
}

int main(void){

    GameSetup();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(green);
        DrawFPS(10, 10);
        Food();
        ProcessInput();
        GameOverCheck();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
