#include <stdio.h>
#include <stdlib.h>
#include "gameobjects.h"
#include "world.h"

GameObjects* createAsteroid(int x, int y) { // creates an asteroid at a given position
    GameObjects* asteroid = (GameObjects*)malloc(sizeof(GameObjects));
    if (asteroid == NULL) {
        // handling memory allocation failure
        printf("Memory allocation failed for asteroid!\n");
        exit(1);  // exit the program if memory allocation fails
    }
    asteroid->type = ASTEROID;  // Set the object type as ASTEROID
    asteroid->x = x;  // x-coordinate
    asteroid->y = y;  // y-coordinate
    return asteroid;  // return the created asteroid object
}

void placeObject(GameObjects* object, int x, int y) { // placing an object in the grid
    grid[y][x] = object;
}

