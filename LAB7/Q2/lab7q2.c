#include <stdio.h>
#include <limits.h>

// Utility function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the Egg Dropping Puzzle using Dynamic Programming
int superEggDrop(int E, int F) {
    // dp[e][f] stores the minimum number of trials for e eggs and f floors
    int dp[E + 1][F + 1];
    int res, x;

    // Initialize base cases
    for (int i = 1; i <= E; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    for (int j = 1; j <= F; j++) {
        dp[1][j] = j;
    }

    // Fill rest of the entries using optimal substructure property
    for (int i = 2; i <= E; i++) {
        for (int j = 2; j <= F; j++) {
            dp[i][j] = INT_MAX;
            for (x = 1; x <= j; x++) {
                res = 1 + max(dp[i - 1][x - 1], dp[i][j - x]);
                if (res < dp[i][j]) {
                    dp[i][j] = res;
                }
            }
        }
    }

    return dp[E][F];
}

int main() {
    // For the specific problem statement: 2 eggs and 100 floors
    int E = 2;
    int F = 100;

    printf("--- Super Egg Drop Problem ---\n");
    printf("Number of Eggs: %d\n", E);
    printf("Number of Floors: %d\n", F);
    printf("Minimum number of drops guaranteed in all cases: %d\n", superEggDrop(E, F));

    return 0;
}
