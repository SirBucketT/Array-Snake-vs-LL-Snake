//
// Created by theodor on 2025-02-03.
//
#include <stdio.h>
#include "header.h"
#include "raylib.h"

interface SnakeAPI{
    // Initialize the snake with a default position and length
    function initSnake(initial_position, initial_length);

    // Update the snake’s position and/or direction each frame
    function updateSnake(direction);

    // Grow the snake by one segment
    function growSnake();

    // Check if the snake collided with walls, itself, etc.
    function checkCollision() -> bool;

    // Retrieve each segment’s position
    // Useful for rendering the snake or for collision detection
    function getSegments() -> list of positions;

    // Free or clear all resources
    function destroySnake();
}


INTERFACE Snake:
    METHOD initSnake(initial_position, initial_length)
    METHOD updateSnake(direction)
    METHOD growSnake()
    METHOD checkCollision() RETURNS boolean
    METHOD getSegments() RETURNS some_list_of_positions
    METHOD destroySnake()