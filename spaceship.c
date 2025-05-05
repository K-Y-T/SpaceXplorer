//
// Created by USER on 30/04/2025.
//
// spaceship.c
#include <stdio.h>
#include "gameobjects.h"
#include "world.h"
#include "spaceship.h"

extern int shieldcool = 0;
extern int turnCounter;  // Turns passed

GameObjects spaceship;

int shieldTurnActivated = -1;  // turncounter = 0 so -1 is used to confirm that shields are off

// creating the spaceship
void initSpaceship() {
    spaceship.x = GRID_SIZE / 2;
    spaceship.y = GRID_SIZE - 3;
    spaceship.type = SPACESHIP;  // icon set
    spaceship.fuel = 50;        // fuel starting value
    spaceship.health = 3;        // max health
    spaceship.shield = 0;        // shields off at start
}

// moving the spaceship based on w, a, s, d input, with bounds checking
void moveSpaceship(char input) {
    grid[spaceship.y][spaceship.x] = NULL;
    if (input == 'w') {
        if (spaceship.y > 1) {
            spaceship.y--;  // up
        } else {
            printf("Cannot move further up!\n");
        }
    } else if (input == 'a') {
        if (spaceship.x > 0) {
            spaceship.x--;  // left
        } else {
            printf("Cannot move left, you are at the left edge!\n");
        }
    } else if (input == 's') {
        if (spaceship.y < GRID_SIZE - 1) {
            spaceship.y++;  // down
        } else {
            printf("Cannot move down, you are at the bottom edge!\n");
        }
    } else if (input == 'd') {
        if (spaceship.x < GRID_SIZE - 1) {
            spaceship.x++;  // right
        } else {
            printf("Cannot move right, you are at the right edge!\n");
        }
    } placeObject(&spaceship, spaceship.x, spaceship.y);
}

// toggling shields
void toggleShield() {
    // Check if there is enough fuel and if the shield can be activated (including cooldown)
    if (spaceship.fuel >= 16 && shieldcool <= 0) {
        // If the shield is not already active, activate it
        if (spaceship.shield == 0) {
            spaceship.shield = 1;  // Activate the shield
            spaceship.fuel -= 15;  // Deduct fuel for shield activation
            spaceship.type = SHIELD;  // Change spaceship symbol to shielded (O)
            shieldTurnActivated = turnCounter;  // Record the turn when shield was activated
            printf("Shield activated for 2 turns!");
        } else {
            printf("Shield is already active, cannot activate again.\n");
        }
    } else {
        printf("Cannot activate shield!\n");
    } checkShields();
}

void checkShields() {
    // Check if the shield is active and deactivate it after 3 turns
    if (spaceship.shield == 1 && turnCounter >= shieldTurnActivated + 3) {
        spaceship.shield = 0;  // Turn off the shield
        spaceship.type = SPACESHIP;  // Change spaceship symbol back to normal (A)
        printf("Shield deactivated.\n");

        // After deactivation, update the spaceship's position on the grid
        placeObject(&spaceship, spaceship.x, spaceship.y);  // Ensure symbol is updated on the grid
        shieldTurnActivated = -1;  // Reset the shield turn counter for the next activation

        // Set cooldown to 3 turns before the shield can be activated again
        shieldcool = 3;
    }

    // Cooldown management (no shield activation for 3 turns after deactivation)
    if (shieldcool > 0) {
        shieldcool--;  // Decrease cooldown each turn
        if (shieldcool > 0) {
            printf("Shield on cooldown. %d turns remaining.\n", shieldcool);
        }
    }
}

// harvesting asteroids and adding fuel
void harvestAsteroid() {
    static int harvestCooldown = 0;

    if (harvestCooldown > 0) {
        harvestCooldown--;  // Cooldown counts down each turn
        printf("Harvesting is on cooldown. %d turns remaining.\n", harvestCooldown);
        return;
    }

    // Check for adjacent asteroids
    for (int i = spaceship.y - 1; i <= spaceship.y + 1; i++) { // starting from top row downwards
        for (int j = spaceship.x - 1; j <= spaceship.x + 1; j++) { // adjacent left column rightwards
            // Ensure we are within grid bounds
            if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE) {
                // If there's an asteroid in an adjacent cell
                if (grid[i][j] != NULL && grid[i][j]->type == ASTEROID) {
                    // harvest this asteroid
                    spaceship.fuel += 10;  // add fuel
                    printf("Asteroid harvested!\n");

                    grid[i][j] = NULL; // Remove the asteroid from the grid
                    placeObject(&spaceship, spaceship.x, spaceship.y);
                    harvestCooldown = 5; // cooldown reset
                    printf("Harvesting is on cooldown. %d turns remaining.\n", harvestCooldown);
                    return;  // Exit after harvesting one asteroid
                }
            }
        }
    }
    printf("No asteroids adjacent to harvest.\n");
    placeObject(&spaceship, spaceship.x, spaceship.y);
}

// reducing health at command
void reduceHealth() {
    if (spaceship.health > 0) {
        spaceship.health--;
        printf("Health reduced!");
    }
}
