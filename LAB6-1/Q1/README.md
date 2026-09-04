# DAA Lab 6 - Question 1: N-th Fibonacci Number using DP

## Problem Statement
Write a program to find the $n$-th Fibonacci number using Dynamic Programming.

## Approach: Bottom-Up Dynamic Programming (Tabulation)
The standard recursive approach for finding Fibonacci numbers has an exponential time complexity of $O(2^n)$ because it recalculates the same subproblems repeatedly. 

To optimize this, the provided C program uses **Dynamic Programming** (specifically, the bottom-up Tabulation method). 
1. We create a 1D array `dp` of size `n + 1` to act as a look-up table.
2. We initialize the base cases: `dp[0] = 0` and `dp[1] = 1`.
3. We iterate from $2$ to $n$, calculating `dp[i] = dp[i-1] + dp[i-2]`.
4. Finally, we return `dp[n]`, which holds the $n$-th Fibonacci number.

*Note: The program uses the `long long` data type to prevent integer overflow, as Fibonacci numbers grow extremely large very quickly.*

## Complexity Analysis
- **Time Complexity:** $O(n)$ — The algorithm uses a single loop that runs from $2$ to $n$, calculating each Fibonacci number exactly once.
- **Space Complexity:** $O(n)$ — An array of size $n + 1$ is used to store the sequence up to the $n$-th term. *(This can be further optimized to $O(1)$ by only storing the last two computed values).*

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a C compiler (like GCC) installed on your system.

### Compilation
Open your terminal and compile the code using the following command:
```bash
gcc q1_fibonacci.c -o fibonacci
