//
// Created by USER on 05/05/2025.
//
#include <stdio.h>
#include "gameobjects.h"
#include "world.h"
#include "spaceship.h"

// Check if the spaceship's motion will result in a collision before moving
void collisionNOMotion(char input) {
    if (spaceship.shield == 0) {  // Only check collisions if shield is off
        if (input == 'w') {  // Move up (check the two cells above the spaceship)
            // Check the cell right above the spaceship
            if (spaceship.y > 0 && grid[spaceship.y - 1][spaceship.x] != NULL) {
                if (spaceship.y > 1 && grid[spaceship.y - 2][spaceship.x] != NULL) {
                    // Collision with two objects
                    printf("Collision detected with two objects! Health reduced by 2.\n");
                    reduceHealth(2);  // Reduce health for two collisions
                    grid[spaceship.y - 1][spaceship.x] = NULL;  // Eliminate first object
                    grid[spaceship.y - 2][spaceship.x] = NULL;  // Eliminate second object
                } else {
                    // Collision with one object
                    printf("Collision detected with one object! Health reduced by 1.\n");
                    reduceHealth(1);  // Reduce health for one collision
                    grid[spaceship.y - 1][spaceship.x] = NULL;  // Eliminate object
                }
                moveAsteroids();  // Move asteroids down after the collision
                // This is where enemies and projectiles motion goes
            } else if (spaceship.y > 1 && grid[spaceship.y - 2][spaceship.x] != NULL) {
                printf("Collision detected with one object! Health reduced by 1.\n");
                reduceHealth(1);  // Reduce health for one collision
                grid[spaceship.y - 2][spaceship.x] = NULL;  // Eliminate object
                moveAsteroids();  // Move asteroids down after the collision
                // This is where enemies and projectiles motion goes
            } else {
                moveAsteroids();  // Move asteroids down after the collision
                // This is where enemies and projectiles motion goes
            }
        } else {  // For all other movements (left, right, down)
            int dx = 0, dy = 0;
            if (input == 'a') dy = 0, dx = -1;  // Left
            if (input == 's') dy = 1, dx = 0;  // Down
            if (input == 'd') dy = 0, dx = 1;  // Right

            moveAsteroids();  // Move asteroids down after the collision
            // This is where enemies and projectiles motion goes

            // Check if there is an object in the next cell in the direction of movement
            if (grid[spaceship.y + dy][spaceship.x + dx] != NULL) {
                // Collision detected
                printf("Collision detected with an object! Health reduced by 1.\n");
                reduceHealth(1);  // Reduce health
                grid[spaceship.y + dy][spaceship.x + dx] = NULL;  // Eliminate object
            }
        }
    } else {  // If shield is active
        // Move asteroids and enemies normally
        moveAsteroids();
        // This is where enemies and projectiles motion goes

        // For all movements, clear the area in front of the spaceship (no health reduction)
        if (input == 'w') {
            // Clear the two cells above the spaceship
            grid[spaceship.y - 1][spaceship.x] = NULL;
            grid[spaceship.y - 2][spaceship.x] = NULL;
        } else {
            // Clear one cell in the direction of movement
            if (input == 'a') grid[spaceship.y][spaceship.x - 1] = NULL;  // Left
            if (input == 's') grid[spaceship.y + 1][spaceship.x] = NULL;  // Down
            if (input == 'd') grid[spaceship.y][spaceship.x + 1] = NULL;  // Right
        }
    }
}
