#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameobjects.h"
#include "spaceship.h"
#include "world.h"

int diff;  // global variable to hold the difficulty level
int turnCounter = 0;

void selectDifficulty() { // difficulty selection
    printf("Select difficulty (1: Easy, 2: Medium, 3: Hard): ");
    scanf("%d", &diff);

    if (diff < 1 || diff > 3) {
        printf("Invalid input, setting difficulty to Easy by default.\n");
        diff = 1; // exception clause for invalid input
    }
}

// Main function
int main() {
    srand(time(NULL));  // seed for rand

    selectDifficulty();

    setDiff(diff); // setting maximum asteroids per row based on selected difficulty level

    createGrid(); // creating the grid and emptying contents

    initSpaceship();
    placeObject(&spaceship, spaceship.x, spaceship.y);

    generateAsteroids(); // creating 8 lines of asteroids as opening to game
    moveAsteroids(); // 1
    moveAsteroids(); // 2
    moveAsteroids(); // 3
    moveAsteroids(); // 4
    moveAsteroids(); // 5
    moveAsteroids(); // 6
    moveAsteroids(); // 7
    moveAsteroids(); // 8

    while (spaceship.health > 0) { // dummy infinite loop to test the world and spaceship integration
        printf("\nTurn: %d      Fuel: %d, Health: %d\n", turnCounter, spaceship.fuel, spaceship.health);

        printGrid();

        // This is where all other game mechanics goes
        char input;
        scanf(" %c", &input);

        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            // Move the spaceship
            moveSpaceship(input);
            placeObject(&spaceship, spaceship.x, spaceship.y);  // Update position on the grid
            turnCounter++;  // Increment the turn counter only after movement
            moveAsteroids();
        } else if (input == 'p') {
            // Toggle the shield
            toggleShield();
        } else if (input == 'h') {
            // Harvest an asteroid
            harvestAsteroid();
        } else {
            printf("Invalid input, try again.\n");
        }
        checkShields();
    }

    return 0;
}
