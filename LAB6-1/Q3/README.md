# DAA Lab 6 - Question 3: Longest Common Subsequence (LCS)

## Problem Statement
Implement the Longest Common Subsequence (LCS) algorithm using Dynamic Programming. Given two strings, find the length of their longest common subsequence and display the subsequence. Analyze the complexity of the algorithm.

## Approach: Bottom-Up Dynamic Programming (Tabulation)
To find the longest common subsequence between two strings `X` (length $m$) and `Y` (length $n$), we use a 2D array approach to avoid the overlapping subproblems of a naive recursive solution.

1. **Building the DP Table (Finding the Length):**
   - We create a 2D array `dp[m + 1][n + 1]`.
   - We iterate through both strings. If the characters match (`X[i-1] == Y[j-1]`), we add 1 to the diagonal value: `dp[i][j] = dp[i-1][j-1] + 1`.
   - If they do not match, we take the maximum value from either excluding the current character of `X` or excluding the current character of `Y`: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
   - The value at `dp[m][n]` gives the length of the LCS.

2. **Backtracking (Finding the Subsequence):**
   - We start from the bottom-right corner of the table (`dp[m][n]`) and trace our way back.
   - If `X[i-1] == Y[j-1]`, this character is part of the LCS. We store it and move diagonally up-left (`i--`, `j--`).
   - If they don't match, we move in the direction of the larger adjacent value (either up or left).

## Complexity Analysis
- **Time Complexity:** $O(m \times n)$ — Building the DP table requires two nested loops iterating $m$ and $n$ times. The backtracking step takes at most $O(m + n)$ time. Thus, the overall time complexity is dominated by the table construction: $O(m \times n)$.
- **Space Complexity:** $O(m \times n)$ — A 2D array of size $(m + 1) \times (n + 1)$ is allocated to store the lengths of longest common subsequences of prefixes.

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a C compiler (like GCC) installed on your system.

### Compilation
Open your terminal and compile the code using the following command:
```bash
gcc q3_lcs.c -o lcs
