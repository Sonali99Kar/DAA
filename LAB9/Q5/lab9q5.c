#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find the minimum number of candies required
int minCandies(int ratings[], int n) {
    if (n <= 0) return 0;

    // Allocate memory for the candies array
    int* candies = (int*)malloc(n * sizeof(int));
    
    // Step 1: Initialize all children with 1 candy
    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }

    // Step 2: Left-to-Right Pass
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // Step 3: Right-to-Left Pass
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i] < candies[i + 1] + 1) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    // Step 4: Calculate total candies
    int totalCandies = 0;
    for (int i = 0; i < n; i++) {
        totalCandies += candies[i];
    }

    free(candies);
    return totalCandies;
}

int main() {
    int ratings[] = {1, 0, 2};
    int n = sizeof(ratings) / sizeof(ratings[0]);

    int result = minCandies(ratings, n);
    printf("Minimum total number of candies needed: %d\n", result);

    return 0;
}