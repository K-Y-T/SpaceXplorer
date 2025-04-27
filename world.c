//
// Created by y2-kalansooriy on 26/04/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "gameobjects.h"

GameObjects* grid[GRID_SIZE][GRID_SIZE]; // defining grid - 2D array of pointers
int maxAsteroidsPR;  // maximum asteroids per row based on difficulty

void createGrid() { // creating the grid and emptying contents
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = NULL;
        }
    }
}

void setDiff(int diff) { // setting maximum asteroids per row based on selected difficulty level
    if (diff == 1) {  // Easy
        maxAsteroidsPR = 3;
    } else if (diff == 2) {  // Medium
        maxAsteroidsPR = 4;
    } else if (diff == 3) {  // Hard
        maxAsteroidsPR = 5;
    }
}

void generateAsteroids() { // generates asteroids on the topmost row of grid
    int asteroidNum = asteroidsToRow();  // get number of asteroids to generate
    if (asteroidNum == 0) return;  // in case there are no asteroids to generate

    for (int i = 0; i < asteroidNum; i++) {
        int position = rand() % GRID_SIZE;  // generate random position in the top row
        GameObjects* asteroid = createAsteroid(position, 0);  // creating asteroid
        placeObject(asteroid, position, 0);  // placing it in the grid
    }
}

void moveAsteroids() { // moves asteroids down the grid, works from the down up
    for (int i = GRID_SIZE - 1; i > 0; i--) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i-1][j] != NULL && grid[i-1][j]->type == ASTEROID) { // if cell not empty and is asteroid
                grid[i][j] = grid[i-1][j];
                grid[i-1][j] = NULL;  // empty the old position
            }
        }
    }
}

void printGrid() { // prints the grid to screen
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == NULL) {
                printf(". ");  // empty space icon
            } else {
                printf("%c ", grid[i][j]->type);  // prints object type
            }
        }
        printf("\n");  // new line after each row
    }
}

int asteroidsToRow() { // generates a random number to decide asteroids in a row
    int dice = rand() % 101;  // random number between 0 and 100

    if (maxAsteroidsPR == 3) {  // Easy
        if (dice <= 20) return 1;
        else if (dice <= 60) return 2;
        else if (dice <= 100) return 3;
        else return 0;
    }
    else if (maxAsteroidsPR == 4) {  // Medium
        if (dice <= 15) return 1;
        else if (dice <= 35) return 2;
        else if (dice <= 75) return 3;
        else if (dice <= 100) return 4;
        else return 0;
    }
    else if (maxAsteroidsPR == 5) {  // Hard
        if (dice <= 10) return 1;
        else if (dice <= 30) return 2;
        else if (dice <= 60) return 3;
        else if (dice <= 85) return 4;
        else return 5;
    }
    return 0;  // default case (shouldn't happen)
}
