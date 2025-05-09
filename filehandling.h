#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <time.h>

// Game result structure
typedef struct {
    char date[11];  // Format: YYYY-MM-DD
    float elapsed_time;  // victory elapsed time in seconds
    int final_fuel;  // Final fuel
    int final_health;  // Final health
    int asteroids_harvested;  // Number of asteroids harvested
    float calculated_value;  // Score
} GameResult;

// Function prototypes
void saveGameResult(float elapsed_time, int final_fuel, int final_health, int asteroids_harvested);
void displayHighScores();
void printRules();

#endif

