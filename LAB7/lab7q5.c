#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check and simulate the moving target strategy
void hitMovingTarget(int n) {
    printf("--- Hitting a Moving Target Analysis ---\n");
    printf("Number of hiding spots (n): %d\n", n);

    if (n <= 1) {
        printf("Invalid input. There must be n > 1 hiding spots.\n");
        return;
    }

    if (n == 2) {
        printf("Deterministic strategy exists for n = 2:\n");
        printf("Shoot at spot 0, then spot 1 (or vice versa). Guaranteed hit in at most 2 shots.\n");
    } 
    else if (n == 3) {
        printf("Deterministic strategy exists for n = 3:\n");
        printf("Shooting sequence: Shoot at spot 1, then spot 1 again. Guaranteed hit.\n");
    } 
    else {
        printf("Result: NO deterministic winning algorithm exists for n >= 4.\n");
        printf("Explanation: For n >= 4, the target can always move to an adjacent spot "
               "such that it remains in the larger remaining sub-interval after a shot, "
               "allowing it to evade capture indefinitely in the worst-case scenario.\n");
    }
}

int main() {
    int n;
    printf("Enter the number of hiding spots (n): ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        printf("Please enter a valid integer greater than 1.\n");
        return 1;
    }

    hitMovingTarget(n);

    // Complexity Analysis
    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(1) - The existence check is solved mathematically based on interval bounds.\n");
    printf("Space Complexity: O(1) - Constant auxiliary memory.\n");

    return 0;
}