//
// Created by y2-kalansooriy on 26/04/2025.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#define GRID_SIZE 18  // globally changeable grid size

// icons for objects
#define ASTEROID '@'
#define SPACESHIP 'A'
#define SHIELD 'O'

// GameObjects structure to represent any object in game
typedef struct {
    char type;   // Type of the object
    int x, y;    // Position in grid
    int fuel;    // Spaceship fuel
    int shield;  // Shield status (1 = active, 0 = inactive)
    int health;  // Spaceship health
} GameObjects;

// Function prototypes
GameObjects* createAsteroid(int x, int y);  // Creating asteroids
void placeObject(GameObjects* object, int x, int y);  // Placing objects in grid

#endif

