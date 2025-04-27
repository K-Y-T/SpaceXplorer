#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameobjects.h"
#include "world.h"

int diff;  // global variable to hold the difficulty level

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

    generateAsteroids(); // creating 8 lines of asteroids as opening to game
    moveAsteroids(); // 1
    generateAsteroids();
    moveAsteroids(); // 2
    generateAsteroids();
    moveAsteroids(); // 3
    generateAsteroids();
    moveAsteroids(); // 4
    generateAsteroids();
    moveAsteroids(); // 5
    generateAsteroids();
    moveAsteroids(); // 6
    generateAsteroids();
    moveAsteroids(); // 7
    generateAsteroids();
    moveAsteroids(); // 8

    while (1) { // dummy infinite loop to test the world function
        generateAsteroids();

        printGrid();

        moveAsteroids();

        // This is where all other game mechanics goes

        printf("Press Enter to continue to the next turn...\n");
        getchar();  // Wait for user input to continue
    }

    return 0;
}