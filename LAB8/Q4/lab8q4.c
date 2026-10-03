#include <stdio.h>
#include <stdlib.h>

// Function to find the length of the Longest Increasing Subsequence
int longestIncreasingSubsequence(int A[], int n) {
    if (n <= 0) return 0;
    
    // dp[i] stores the LIS length ending at index i
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Initialize LIS values for all indexes as 1
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    // Compute optimized LIS values in bottom-up manner
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }
    
    // Pick the maximum overall LIS value
    int max_lis = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > max_lis) {
            max_lis = dp[i];
        }
    }
    
    free(dp);
    return max_lis;
}

int main() {
    int n;
    
    // Proper input representation: Dynamic allocation of array size and elements
    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for array size.\n");
        return 1;
    }
    
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    int lis_length = longestIncreasingSubsequence(A, n);
    
    printf("\n--- Results ---\n");
    printf("Array: [ ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("]\n");
    printf("Length of Longest Increasing Subsequence: %d\n", lis_length);
    
    free(A);
    return 0;
}