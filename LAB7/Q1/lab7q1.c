#include <stdio.h>
#include <math.h>

// Function to calculate minimum moves to invert a coin triangle of 'n' rows
int minMovesToInvert(int n) {
    // Using the standard formula for coin-triangle inversion moves: floor(n/2) * ceil(n/2)
    int moves = (n / 2) * ((n + 1) / 2);
    return moves;
}

int main() {
    int n;
    printf("Enter the number of rows (n) in the coin triangle: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a valid positive integer for rows.\n");
        return 1;
    }

    int total_coins = (n * (n + 1)) / 2;
    int moves = minMovesToInvert(n);

    printf("\n--- Coin Triangle Inversion Results ---\n");
    printf("Number of rows (n): %d\n", n);
    printf("Total coins in the triangle: %d\n", total_coins);
    printf("Minimum moves required to invert: %d\n", moves);

    // Complexity Analysis
    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(1) \n");
    printf("Space Complexity: O(1) \n");

    return 0;
}
