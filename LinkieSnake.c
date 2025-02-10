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

typedef struct SnakeNode {
    Vector2 position;
    struct SnakeNode* next;
} SnakeNode;

struct GameState {
    SnakeNode* snakeHead;
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

    gameState.snakeHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    gameState.snakeHead->position.x = centerX;
    gameState.snakeHead->position.y = centerY;
    gameState.snakeHead->next = NULL;

    SnakeNode* current = gameState.snakeHead;
    for (int i = 1; i < gameState.snakeLength; i++) {
        SnakeNode* newSegment = (SnakeNode*)malloc(sizeof(SnakeNode));
        newSegment->position.x = centerX - i;
        newSegment->position.y = centerY;
        newSegment->next = NULL;
        current->next = newSegment;
        current = newSegment;
    }
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
        if ((IsKeyPressed(KEY_UP)   || IsKeyPressed(KEY_W)) && gameState.currentDirection != DIR_DOWN) {
            gameState.currentDirection = DIR_UP;
        }
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && gameState.currentDirection != DIR_UP) {
            gameState.currentDirection = DIR_DOWN;
        }
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && gameState.currentDirection != DIR_RIGHT) {
            gameState.currentDirection = DIR_LEFT;
        }
        if ((IsKeyPressed(KEY_RIGHT)|| IsKeyPressed(KEY_D)) && gameState.currentDirection != DIR_LEFT) {
            gameState.currentDirection = DIR_RIGHT;
        }
    }

    if (gameState.framesCounter >= GAME_SPEED) {
        gameState.framesCounter = 0;

        // Move the snake by shifting all segments
        SnakeNode* prev = NULL;
        SnakeNode* current = gameState.snakeHead;
        Vector2 prevPos = current->position;

        // Move the head
        switch (gameState.currentDirection) {
            case DIR_UP:    current->position.y -= 1; break;
            case DIR_DOWN:  current->position.y += 1; break;
            case DIR_LEFT:  current->position.x -= 1; break;
            case DIR_RIGHT: current->position.x += 1; break;
        }

        // Move the body
        while (current->next != NULL) {
            prev = current;
            current = current->next;
            Vector2 tempPos = current->position;
            current->position = prevPos;
            prevPos = tempPos;
        }
    }

    // Check collision with walls
    if (gameState.snakeHead->position.x < 0 || gameState.snakeHead->position.x >= SCREEN_WIDTH / CELL_SIZE ||
        gameState.snakeHead->position.y < 0 || gameState.snakeHead->position.y >= SCREEN_HEIGHT / CELL_SIZE) {
        gameState.gameOver = true;
    }
}

void DrawSnake(void) {
    SnakeNode* current = gameState.snakeHead;
    bool first = true;
    while (current != NULL) {
        DrawRectangle(
            (int)current->position.x * CELL_SIZE,
            (int)current->position.y * CELL_SIZE,
            CELL_SIZE, CELL_SIZE,
            first ? GREEN : BLACK
        );
        first = false;
        current = current->next;
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
    DrawText(TextFormat("Score %d", gameState.score), SCREEN_WIDTH / 2, 20, 25, BLACK);

    DrawRectangle(
        (int)gameState.foodPosition.x * CELL_SIZE,
        (int)gameState.foodPosition.y * CELL_SIZE,
        CELL_SIZE, CELL_SIZE,
        RED
    );

    if (gameState.snakeHead->position.x == gameState.foodPosition.x &&
        gameState.snakeHead->position.y == gameState.foodPosition.y) {

        gameState.score++;
        gameState.snakeLength++;

        SnakeNode* tail = gameState.snakeHead;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        SnakeNode* newSegment = (SnakeNode*)malloc(sizeof(SnakeNode));
        newSegment->position = tail->position;
        newSegment->next = NULL;
        tail->next = newSegment;

        gameState.foodPosition.x = rand() % (SCREEN_WIDTH / CELL_SIZE);
        gameState.foodPosition.y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
        }
}

void GameOverCheck(void) {
    if (gameState.gameOver) {
        DrawText("Game Over", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 30, BLACK);
    }
}

void FreeSnake(void) {
    SnakeNode* current = gameState.snakeHead;
    while (current != NULL) {
        SnakeNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    GameSetup();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(green);
        Food();
        ProcessInput();
        DrawSnake();
        GameOverCheck();
        EndDrawing();
    }

    FreeSnake();
    CloseWindow();
    return 0;
}

