#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

#define SCREEN_WIDTH   1800
#define SCREEN_HEIGHT  900

struct Color green = {173, 204, 96, 255};
struct Color darkGreen = {43, 51, 24, 255};

struct Circle {
    Vector2 center;
    float radius;
};

typedef struct {
    struct Circle shape;
    bool active;
    Color darkGreen;
} Food;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake.. Snake.. SNAKE!");

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}