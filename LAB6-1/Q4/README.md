# DAA Lab 6 - Question 4: Matrix Chain Multiplication using DP

## Problem Statement
Write a program to implement Matrix Chain Multiplication using Dynamic Programming. Given the dimensions of $N-1$ matrices in an array `arr[]`, determine the minimum number of scalar multiplications required to multiply the complete matrix chain.

## Approach: Bottom-Up Dynamic Programming
The Matrix Chain Multiplication problem asks for the most efficient way to multiply a given sequence of matrices. The goal is not to perform the multiplications, but to decide the optimal sequence (where to place the parentheses) to minimize the total scalar multiplications.

We solve this using a tabulation DP approach:
1. We create a 2D array `dp[N][N]`, where `dp[i][j]` stores the minimum number of scalar multiplications needed to compute the product of matrices from $i$ to $j$ ($A_i \dots A_j$).
2. The dimensions of matrix $A_i$ are given by `arr[i-1] x arr[i]`.
3. We iteratively solve for chains of increasing length, starting from $L = 2$ up to $N-1$.
4. For each sub-chain of length $L$ from index $i$ to $j$, we try all possible split points $k$ (where $i \le k < j$).
5. The cost of a split at $k$ is calculated as:
   `cost = dp[i][k] + dp[k+1][j] + (arr[i-1] * arr[k] * arr[j])`
6. We find the minimum cost among all possible split points $k$ and store it in `dp[i][j]`.
7. The overall minimum cost for the entire matrix chain is found in `dp[1][N-1]`.

## Complexity Analysis
- **Time Complexity:** $O(N^3)$ — The algorithm uses three nested loops: one for the chain length $L$, one for the starting index $i$, and one for the split point $k$. This matches the target time complexity specified in the assignment.
- **Space Complexity:** $O(N^2)$ — A 2D array of size $N \times N$ is used to store the intermediate minimum costs of the subproblems.

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a C compiler (like GCC) installed on your system.

### Compilation
Open your terminal and compile the code using the following command:
```bash
gcc q4_mcm.c -o mcm
