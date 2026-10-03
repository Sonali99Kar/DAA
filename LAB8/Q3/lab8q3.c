#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute LCS length and reconstruct the LCS string
void computeAndPrintLCS(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    // Proper input representation: Dynamically allocate 2D DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc((n + 1), sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    
    // Fill the DP table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    int lcs_length = dp[m][n];
    
    // Reconstruct the LCS string from the DP table via traceback
    char *lcs_str = (char *)malloc((lcs_length + 1) * sizeof(char));
    if (lcs_str == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    lcs_str[lcs_length] = '\0'; // Null-terminate string
    
    int i = m, j = n, index = lcs_length;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_str[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    // Display results
    printf("\n--- Results ---\n");
    printf("Sequence X: %s\n", X);
    printf("Sequence Y: %s\n", Y);
    printf("Length of LCS: %d\n", lcs_length);
    printf("Longest Common Subsequence: %s\n", lcs_str);
    
    // Free allocated memory
    free(lcs_str);
    for (int k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);
}

int main() {
    // Dynamic string buffers for robust input representation
    char *X = (char *)malloc(100 * sizeof(char));
    char *Y = (char *)malloc(100 * sizeof(char));
    
    if (X == NULL || Y == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter sequence X: ");
    if (scanf("%99s", X) != 1) {
        printf("Invalid input.\n");
        free(X);
        free(Y);
        return 1;
    }
    
    printf("Enter sequence Y: ");
    if (scanf("%99s", Y) != 1) {
        printf("Invalid input.\n");
        free(X);
        free(Y);
        return 1;
    }
    
    computeAndPrintLCS(X, Y);
    
    free(X);
    free(Y);
    return 0;
}