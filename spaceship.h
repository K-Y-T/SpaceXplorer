#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "gameobjects.h"  // Include the game objects header

// Declare the spaceship object (which is a GameObjects structure)
extern GameObjects spaceship;  // Spaceship is a global GameObjects instance

// Function prototypes for spaceship-related actions
void initSpaceship();         // Initialize the spaceship with starting values (position, fuel, health, etc.)
void moveSpaceship(char input);  // Move the spaceship based on user input ('w', 'a', 's', 'd')
void toggleShield();            // Activate/deactivate shield and handle fuel
void checkShields();
void harvestAsteroid();         // Harvest an asteroid and add fuel
void reduceHealth(int value);            // Reduce the spaceship's health

#endif //SPACESHIP_H
