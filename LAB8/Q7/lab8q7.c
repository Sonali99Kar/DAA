#include <stdio.h>
#include <stdlib.h>

// Function to solve Rod Cutting and print maximum revenue along with piece lengths
void rodCuttingWithReconstruction(int P[], int n) {
    // dp[i] stores the maximum revenue for rod length i
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    // s[i] stores the first cut size for rod length i to reconstruct the solution
    int *s = (int *)malloc((n + 1) * sizeof(int));
    
    if (dp == NULL || s == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    dp[0] = 0;
    
    // Compute optimal revenue and cut locations bottom-up
    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        int best_cut = -1;
        for (int j = 1; j <= i; j++) {
            // P[j-1] corresponds to price of piece of length j (1-indexed mapping)
            if (P[j - 1] + dp[i - j] > max_val) {
                max_val = P[j - 1] + dp[i - j];
                best_cut = j;
            }
        }
        dp[i] = max_val;
        s[i] = best_cut;
    }
    
    printf("\n--- Results ---\n");
    printf("Rod Length n: %d\n", n);
    printf("Maximum Revenue Obtainable: %d\n", dp[n]);
    
    // Reconstruct optimal piece lengths
    printf("Optimal Piece Decomposition: ");
    int temp_n = n;
    while (temp_n > 0) {
        printf("%d ", s[temp_n]);
        temp_n -= s[temp_n];
    }
    printf("\n");
    
    free(dp);
    free(s);
}

int main() {
    int n;
    
    printf("Enter the length of the rod (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for rod length.\n");
        return 1;
    }
    
    int *P = (int *)malloc(n * sizeof(int));
    if (P == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter the prices for lengths 1 to %d:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i]);
    }
    
    rodCuttingWithReconstruction(P, n);
    
    free(P);
    return 0;
}