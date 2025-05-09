#ifndef WORLD_H
#define WORLD_H

#include "gameobjects.h"

extern GameObjects* grid[GRID_SIZE][GRID_SIZE];

// Function prototypes
void createGrid();
void setDiff(int diff); // Value returned from main
void generateAsteroids();
void moveAsteroids();
int asteroidsToRow();
void printGrid();

#endif

