#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to find the minimum of three numbers
int min(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

// Function to compute edit distance and print traceback operations
void computeEditDistanceWithTraceback(char *A, char *B) {
    int m = strlen(A);
    int n = strlen(B);
    
    // Proper input representation: Dynamically allocate 2D DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    
    // Initialize base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    // Fill the DP table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(
                    dp[i - 1][j],    // Deletion
                    dp[i][j - 1],    // Insertion
                    dp[i - 1][j - 1] // Substitution
                );
            }
        }
    }
    
    printf("\n--- Results ---\n");
    printf("Source String A: %s\n", A);
    printf("Target String B: %s\n", B);
    printf("Minimum Edit Distance: %d\n", dp[m][n]);
    
    // Traceback to print operations from the end to the beginning
    printf("\nDetailed Traceback Operations:\n");
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            printf("Match: Character '%c'\n", A[i - 1]);
            i--;
            j--;
        } else {
            int sub_cost = (i > 0 && j > 0) ? dp[i - 1][j - 1] : 999999;
            int del_cost = (i > 0) ? dp[i - 1][j] : 999999;
            int ins_cost = (j > 0) ? dp[i][j - 1] : 999999;
            
            // Prioritize match/substitution if costs align, or choose minimum operation
            if (i > 0 && j > 0 && dp[i][j] == sub_cost + 1) {
                printf("Substitute '%c' with '%c'\n", A[i - 1], B[j - 1]);
                i--;
                j--;
            } else if (i > 0 && dp[i][j] == del_cost + 1) {
                printf("Delete '%c'\n", A[i - 1]);
                i--;
            } else if (j > 0 && dp[i][j] == ins_cost + 1) {
                printf("Insert '%c'\n", B[j - 1]);
                j--;
            }
        }
    }
    
    // Free allocated memory
    for (int k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);
}

int main() {
    char *A = (char *)malloc(100 * sizeof(char));
    char *B = (char *)malloc(100 * sizeof(char));
    
    if (A == NULL || B == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter string A: ");
    if (scanf("%99s", A) != 1) {
        printf("Invalid input.\n");
        free(A);
        free(B);
        return 1;
    }
    
    printf("Enter string B: ");
    if (scanf("%99s", B) != 1) {
        printf("Invalid input.\n");
        free(A);
        free(B);
        return 1;
    }
    
    computeEditDistanceWithTraceback(A, B);
    
    free(A);
    free(B);
    return 0;
}