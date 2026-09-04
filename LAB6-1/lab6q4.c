#include <stdio.h>
#include <limits.h> // For INT_MAX

// Function to find the minimum number of multiplications
int matrixChainOrder(int arr[], int N) {
    
    int dp[N][N];
    int i, j, k, L, q;

    for (i = 1; i < N; i++) {
        dp[i][i] = 0;
    }

    for (L = 2; L < N; L++) {
        for (i = 1; i < N - L + 1; i++) {
            j = i + L - 1;
            dp[i][j] = INT_MAX; 
            for (k = i; k <= j - 1; k++) {
                q = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                }
            }
        }
    }
    return dp[1][N - 1];
}

int main() {
    int arr[] = {10, 30, 5, 60};
    int N = sizeof(arr) / sizeof(arr[0]);

    printf("Input array: {");
    for(int i = 0; i < N; i++) {
        printf("%d%s", arr[i], (i < N - 1) ? ", " : "}\n");
    }
    printf("N = %d\n\n", N);

    // Call the function and print the result
    printf("Output: %d\n", matrixChainOrder(arr, N));

    return 0;
}