#include <stdio.h>
#include <stdlib.h>

// Structure to represent a scientist's lifespan
typedef struct {
    int birth;
    int death;
} Scientist;

// Comparison function for sorting years in ascending order
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to find the year with the maximum living scientists
void findBestTimeToAlive(Scientist scientists[], int n) {
    int *births = (int *)malloc(n * sizeof(int));
    int *deaths = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        births[i] = scientists[i].birth;
        deaths[i] = scientists[i].death;
    }

    // Sort birth and death years independently
    qsort(births, n, sizeof(int), compare);
    qsort(deaths, n, sizeof(int), compare);

    int i = 0, j = 0;
    int current_alive = 0;
    int max_alive = 0;
    int best_year = births[0];

    // Two-pointer traversal over sorted timelines
    while (i < n) {
        // If birth year is less than or equal to death year, a scientist is added
        // (Using <= handles the problem rule that death happens before birth in the same year)
        if (births[i] <= deaths[j]) {
            current_alive++;
            if (current_alive > max_alive) {
                max_alive = current_alive;
                best_year = births[i];
            }
            i++;
        } else {
            // A scientist has died
            current_alive--;
            j++;
        }
    }

    printf("--- The Best Time to Be Alive Analysis ---\n");
    printf("Year with the maximum number of living scientists: %d\n", best_year);
    printf("Maximum number of prominent scientists alive simultaneously: %d\n", max_alive);

    free(births);
    free(deaths);
}

int main() {
    // Sample dataset of scientists (birth, death)
    Scientist scientists[] = {
        {1500, 1560},
        {1520, 1590},
        {1550, 1610},
        {1540, 1600},
        {1545, 1585}
    };
    int n = sizeof(scientists) / sizeof(scientists[0]);

    findBestTimeToAlive(scientists, n);

    // Complexity Analysis
    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(n log n) - Dominated by sorting the birth and death year arrays of size n.\n");
    printf("Space Complexity: O(n) - Auxiliary storage used for separated birth and death arrays.\n");

    return 0;
}
