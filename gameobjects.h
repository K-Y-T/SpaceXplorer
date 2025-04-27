//
// Created by y2-kalansooriy on 26/04/2025.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#define GRID_SIZE 18  // globally changeable grid size

// icons for objects
#define ASTEROID '@'

// GameObjects structure to represent any object in game
typedef struct {
    char type;   // Type of the object
    int x, y;    // Position in grid
} GameObjects;

// Function prototypes
GameObjects* createAsteroid(int x, int y);  // Creating asteroids
void placeObject(GameObjects* object, int x, int y);  // Placing objects in grid

#endif

