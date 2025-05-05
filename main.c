#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameobjects.h"
#include "spaceship.h"
#include "world.h"
#include "collision.h"
#include "filehandling.h"

int diff;  // global variable to hold the difficulty level
int turnCounter = 0;
int asteroidsHarvested = 0;  // Counter for number of asteroids harvested
int maxTurns = 60;  // Set a fixed number of turns for the player to survive (example)
time_t startTime;
extern int harvestCooldown;

void selectDifficulty() { // difficulty selection
    printf("Select difficulty (1: Easy, 2: Medium, 3: Hard): ");
    scanf("%d", &diff);

    if (diff < 1 || diff > 3) {
        printf("Invalid input, setting difficulty to Easy by default.\n");
        diff = 1; // exception clause for invalid input
    }
}

// Function to check for win/loss
void checkWinLoss() {
    if (spaceship.health <= 0) {
        printf("You lost! Health reached zero.\n");
        exit(0);  // End the game if health reaches zero
    }

    if (spaceship.fuel == 0) {
        printf("You lost! Fuel ran out.\n");
        exit(0);
    }

    if (turnCounter >= maxTurns) {
        printf("You won! You survived for %d turns.\n", maxTurns);
        saveGameResult(difftime(time(NULL), startTime), spaceship.fuel, spaceship.health, asteroidsHarvested);
        exit(0);  // End the game if the player survives the set number of turns
    }
}

// Main function
int main() {
    srand(time(NULL));  // seed for rand
    time_t startTime = time(NULL);  // Capture the starting time

    char menuOption;
    while (1) {
        printf("\nMain Menu:\n");
        printf("n - New Game\n");
        printf("r - Rules\n");
        printf("h - Highscores\n");
        printf("e - Exit\n");
        printf("Select an option: ");
        scanf(" %c", &menuOption);

        if (menuOption == 'n') {
            // Start new game
            selectDifficulty();

            setDiff(diff); // setting maximum asteroids per row based on selected difficulty level

            createGrid(); // creating the grid and emptying contents

            initSpaceship();
            placeObject(&spaceship, spaceship.x, spaceship.y);

            generateAsteroids(); // creating 8 lines of asteroids as opening to game
            for (int i = 0; i < 8; i++) {
                moveAsteroids();
            }

            while (spaceship.health > 0) { // dummy infinite loop to test the world and spaceship integration
                printf("\nTurn: %d      Fuel: %d, Health: %d\n", turnCounter, spaceship.fuel, spaceship.health);

                printGrid();

                // This is where all other game mechanics goes
                char input;
                scanf(" %c", &input);

                if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                    collisionNOMotion(input);
                    // Move the spaceship
                    moveSpaceship(input);
                    placeObject(&spaceship, spaceship.x, spaceship.y);  // Update position on the grid
                    turnCounter++;  // Increment the turn counter only after movement
                    spaceship.fuel--;

                    if (harvestCooldown > 0) {
                        harvestCooldown--;  // Decrease the cooldown each turn
                    }

                } else if (input == 'p') {
                    // Toggle the shield
                    toggleShield();
                } else if (input == 'h') {
                    // Harvest an asteroid
                    harvestAsteroid();
                    asteroidsHarvested++;
                } else {
                    printf("Invalid input, try again.\n");
                }
                checkWinLoss();
                checkShields();
            }
        } else if (menuOption == 'r') {
            printRules();
        } else if (menuOption == 'h') {
            displayHighScores();
        } else if (menuOption == 'e') {
            char confirmExit;
            printf("Are you sure you want to exit? (y/n): ");
            scanf(" %c", &confirmExit);
            if (confirmExit == 'y') {
                printf("Exiting game...\n");
                break;
            }
        } else {
            printf("Invalid option, please try again.\n");
        }
    }

    return 0;
}
