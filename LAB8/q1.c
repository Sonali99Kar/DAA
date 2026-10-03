#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the minimum number of coins needed
int minCoinChange(int C[], int n, int V) {
    // dp[i] will store the minimum coins needed for amount i
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Initialize DP table with a value representing infinity
    for (int i = 0; i <= V; i++) {
        dp[i] = INT_MAX;
    }
    
    // Base case: 0 coins required for amount 0
    dp[0] = 0;
    
    // Compute minimum coins for all amounts from 1 to V
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (C[j] <= i) {
                int sub_res = dp[i - C[j]];
                // Check if sub_res is not infinity and can form a valid solution
                if (sub_res != INT_MAX && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }
    
    int result = dp[V];
    free(dp);
    
    // If result is still INT_MAX, amount cannot be made up
    return (result == INT_MAX) ? -1 : result;
}

int main() {
    int n, V;
    
    // Proper input representation: Dynamic reading of coin array size and denominations
    printf("Enter the number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for number of coins.\n");
        return 1;
    }
    
    int *C = (int *)malloc(n * sizeof(int));
    if (C == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter the coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
    }
    
    printf("Enter the target amount V: ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid input for target amount.\n");
        free(C);
        return 1;
    }
    
    int min_coins = minCoinChange(C, n, V);
    
    printf("\n--- Result ---\n");
    printf("Coin Denominations: ");
    for (int i = 0; i < n; i++) printf("%d ", C[i]);
    printf("\nTarget Amount V: %d\n", V);
    
    if (min_coins != -1) {
        printf("Minimum number of coins required: %d\n", min_coins);
    } else {
        printf("The target amount cannot be made up with the given coins (-1).\n");
    }
    
    free(C);
    return 0;
}
