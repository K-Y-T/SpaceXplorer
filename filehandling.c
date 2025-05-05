//
// Created by USER on 05/05/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filehandling.h"

#define FILENAME "highscores.txt"

// Function to save the game result to the file
void saveGameResult(float elapsed_time, int final_fuel, int final_health, int asteroids_harvested) {
    FILE *file = fopen(FILENAME, "a");  // Open file in append mode
    if (file == NULL) {
        printf("Error opening file to save result.\n");
        return;
    }

    // Calculate the calculated value based on the rules
    float calculated_value = 0;
    calculated_value += 1.0f / (elapsed_time + 1);  // Least time, the better (inversely)
    calculated_value += final_fuel / 50.0f;  // Most fuel, the better
    calculated_value += final_health / 3.0f;  // Most health, the better
    calculated_value -= asteroids_harvested / 10.0f;  // Least asteroids, the better

    // Get the current date in YYYY-MM-DD format
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[11];
    sprintf(date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    // Write the result to the file
    fprintf(file, "%s %.2f %d %d %d %.2f\n", date, elapsed_time, final_fuel, final_health, asteroids_harvested, calculated_value);

    fclose(file);  // Close the file
}

// Function to display high scores (top 5)
void displayHighScores() {
    FILE *file = fopen(FILENAME, "r");  // Open file in read mode
    if (file == NULL) {
        printf("No high score data available.\n");
        return;
    }

    // Array to store all results from the file
    GameResult results[100];  // Allocate memory for a larger number of records (100 here, adjust as needed)
    int count = 0;

    // Read all game results from the file
    while (fscanf(file, "%s %f %d %d %d %f", results[count].date, &results[count].elapsed_time,
                  &results[count].final_fuel, &results[count].final_health, &results[count].asteroids_harvested,
                  &results[count].calculated_value) != EOF) {
        count++;
    }

    fclose(file);  // Close the file

    // Sort the results by calculated value (descending order)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (results[i].calculated_value < results[j].calculated_value) {
                // Swap the elements
                GameResult temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }
    }

    // Display the top 5 scores
    printf("\nTop 5 High Scores:\n");
    for (int i = 0; i < (count < 5 ? count : 5); i++) {
        printf("%d. Date: %s | Time: %.2f | Fuel: %d | Health: %d | Asteroids Harvested: %d | Score: %.2f\n",
               i + 1, results[i].date, results[i].elapsed_time, results[i].final_fuel, results[i].final_health,
               results[i].asteroids_harvested, results[i].calculated_value);
    }
}

// Function to print the game rules and controls
void printRules() {
    printf("\nGame Rules:\n");
    printf("The objective of the game is to survive while avoiding asteroids.\n");
    printf("Control your spaceship with the following keys:\n");
    printf("   - 'w' to move up\n");
    printf("   - 'a' to move left\n");
    printf("   - 's' to move down\n");
    printf("   - 'd' to move right\n");
    printf("3. Press 'p' to activate a shield (consumes 15 fuel, turns on for two turns, goes into cooldown for three turns after deactivating).\n");
    printf("4. Press 'h' to harvest asteroids and gain fuel (adds 10 fuel, you can only harvest once per 5 turns).\n");
    printf("5. Your fuel decreases over time. Use it wisely!\n");
    printf("6. If you collide with an asteroid, you lose health. If health reaches zero, you lose the game.\n");
    printf("7. To win, survive for 60 turns!\n");
}

