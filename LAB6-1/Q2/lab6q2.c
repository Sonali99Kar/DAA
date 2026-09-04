#include <stdio.h>

// A simple helper function to find the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem using DP
int knapsack(int W, int weights[], int profits[], int n) {
    int i, w;
   
    int dp[n + 1][W + 1];

    // Build the table bottom-up
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            // Base case: If there are no items or the capacity is 0, profit is 0
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } 
            // If the current item's weight is less than or equal to the current capacity
            else if (weights[i - 1] <= w) {
             
                dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } 
            // If the current item's weight is greater than the capacity, we CANNOT include it
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right cell contains our final maximum profit
    return dp[n][W];
}

int main() {
    // Example data
    int profits[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int W = 50; // Total capacity of the knapsack
    int n = sizeof(profits) / sizeof(profits[0]); // Number of items

    printf("The maximum profit that can be obtained is: %d\n", knapsack(W, weights, profits, n));

    return 0;
}
