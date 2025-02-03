#include <stdio.h>
#include "header.h"
#include "raylib.h"

#define SCREEN_WIDTH   1800
#define SCREEN_HEIGHT  900

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake.. Snake.. SNAKE!");

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);

    }
    EndDrawing();
    CloseWindow();
    return 0;
}