#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum sum of a strictly increasing subsequence
int maxSumIncreasingSubsequence(int A[], int n) {
    if (n <= 0) return 0;
    
    // dp[i] stores the maximum increasing subsequence sum ending at index i
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Initialize dp values with the elements of the array themselves
    for (int i = 0; i < n; i++) {
        dp[i] = A[i];
    }
    
    // Compute optimized MSIS values in bottom-up manner
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j] && dp[i] < dp[j] + A[i]) {
                dp[i] = dp[j] + A[i];
            }
        }
    }
    
    // Find the maximum value in the dp array
    int max_sum = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }
    
    free(dp);
    return max_sum;
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
    
    printf("Enter the positive integer elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    int msis_result = maxSumIncreasingSubsequence(A, n);
    
    printf("\n--- Results ---\n");
    printf("Array: [ ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("]\n");
    printf("Maximum Sum Increasing Subsequence: %d\n", msis_result);
    
    free(A);
    return 0;
}