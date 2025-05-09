#include <stdio.h>
#include "gameobjects.h"
#include "world.h"
#include "spaceship.h"

// checking if the spaceship's motion will result in a collision before moving
void collisionNOMotion(char input) {
    if (spaceship.shield == 0) {  // Only check collisions if shield is off
        if (input == 'w') {  // upwards motion special case
            if (spaceship.y > 0 && grid[spaceship.y - 1][spaceship.x] != NULL) {
                if (spaceship.y > 1 && grid[spaceship.y - 2][spaceship.x] != NULL) { // two collisions
                    printf("Collision detected with two objects! Health reduced by 2.\n");
                    reduceHealth(2);  // Reduce health for two collisions
                    grid[spaceship.y - 1][spaceship.x] = NULL;  // remove first asteroid
                    grid[spaceship.y - 2][spaceship.x] = NULL;  // remove second asteroid
                } else { // one collision
                    printf("Collision detected with one object! Health reduced by 1.\n");
                    reduceHealth(1);  // reduce health for one collision
                    grid[spaceship.y - 1][spaceship.x] = NULL;  // remove asteroid
                }
                moveAsteroids();
            } else if (spaceship.y > 1 && grid[spaceship.y - 2][spaceship.x] != NULL) {
                printf("Collision detected with one object! Health reduced by 1.\n");
                reduceHealth(1);  // Reduce health for one collision
                grid[spaceship.y - 2][spaceship.x] = NULL;  // remove asteroid
                moveAsteroids();
            } else {
                moveAsteroids();
            }
        } else {  // For all other movements (left, right, down)
            int dx = 0, dy = 0;
            if (input == 'a') dy = 0, dx = -1;  // Left
            if (input == 's') dy = 1, dx = 0;  // Down
            if (input == 'd') dy = 0, dx = 1;  // Right

            moveAsteroids(); // first move asteroids before collision check

            // checking if there is an object in the next cell in the direction of movement
            if (grid[spaceship.y + dy][spaceship.x + dx] != NULL) { // one collision
                printf("Collision detected with an object! Health reduced by 1.\n");
                reduceHealth(1);
                grid[spaceship.y + dy][spaceship.x + dx] = NULL;  // remove asteroid
            }
        }
    } else {  // If shield is active
        // Move asteroids normally
        moveAsteroids();

        // clearing grid cells corresponding to spaceship movement
        if (input == 'w') {
            grid[spaceship.y - 1][spaceship.x] = NULL;
            grid[spaceship.y - 2][spaceship.x] = NULL;
        } else {
            if (input == 'a') grid[spaceship.y][spaceship.x - 1] = NULL;  // Left
            if (input == 's') grid[spaceship.y + 1][spaceship.x] = NULL;  // Down
            if (input == 'd') grid[spaceship.y][spaceship.x + 1] = NULL;  // Right
        }
    }
}
