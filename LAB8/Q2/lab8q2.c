#include <stdio.h>
#include <stdlib.h>

// Recursive function to print all unique combinations that sum up to V
void printCombinations(int C[], int n, int target, int current_coin_index, int *current_combination, int level) {
    if (target == 0) {
        printf("{ ");
        for (int i = 0; i < level; i++) {
            printf("%d ", current_combination[i]);
        }
        printf("}\n");
        return;
    }
    
    for (int i = current_coin_index; i < n; i++) {
        if (target >= C[i]) {
            current_combination[level] = C[i];
            printCombinations(C, n, target - C[i], i, current_combination, level + 1);
        }
    }
}

// Function to find the total number of distinct combinations and list them
long long countAndPrintCoinChangeWays(int C[], int n, int V) {
    long long *dp = (long long *)calloc((V + 1), sizeof(long long));
    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    dp[0] = 1;
    
    for (int j = 0; j < n; j++) {
        for (int i = C[j]; i <= V; i++) {
            dp[i] += dp[i - C[j]];
        }
    }
    
    long long total_ways = dp[V];
    free(dp);
    return total_ways;
}

int main() {
    int n, V;
    
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
    
    long long total_ways = countAndPrintCoinChangeWays(C, n, V);
    
    printf("\n--- Results ---\n");
    printf("Coin Denominations: ");
    for (int i = 0; i < n; i++) printf("%d ", C[i]);
    printf("\nTarget Amount V: %d\n", V);
    printf("Total number of distinct combinations: %lld\n", total_ways);
    
    if (total_ways > 0) {
        printf("\nDetailed Combinations:\n");
        int *current_combination = (int *)malloc(V * sizeof(int));
        printCombinations(C, n, V, 0, current_combination, 0);
        free(current_combination);
    }
    
    free(C);
    return 0;
}