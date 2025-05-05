//
// Created by USER on 05/05/2025.
//

#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <time.h>

// Game result structure
typedef struct {
    char date[11];  // Format: YYYY-MM-DD
    float elapsed_time;  // Time elapsed to win (in seconds)
    int final_fuel;  // Final fuel (capped at 50)
    int final_health;  // Final health (capped at 3)
    int asteroids_harvested;  // Number of asteroids harvested
    float calculated_value;  // Final score based on the calculated formula
} GameResult;

// Function prototypes
void saveGameResult(float elapsed_time, int final_fuel, int final_health, int asteroids_harvested);
void displayHighScores();
void printRules();

#endif

