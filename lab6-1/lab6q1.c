#include <stdio.h>

// Function to find the nth Fibonacci number using Dynamic Programming
long long fibonacci(int n) {
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Create an array to store Fibonacci numbers
    long long dp[n + 1];

    dp[0] = 0;
    dp[1] = 1;

    // Build the DP table bottom-up
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    // Return the Fibonacci number
    return dp[n];
}

int main() {
    int n;
    
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Please enter a valid non-negative integer.\n");
    } else {
        printf("The %d-th Fibonacci number is: %lld\n", n, fibonacci(n));
    }

    return 0;
}
