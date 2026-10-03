# Lab-08: Question 3 - Longest Common Subsequence (LCS)

## Problem Statement
Given two sequences $X = \langle x_1, x_2, \dots, x_m \rangle$ and $Y = \langle y_1, y_2, \dots, y_n \rangle$, compute the length of their longest common subsequence and reconstruct the actual subsequence string.

---

## Algorithm Design (Dynamic Programming)
This problem exhibits optimal substructure and overlapping subproblems, making Dynamic Programming the ideal approach:

* **State Definition:** Let `dp[i][j]` represent the length of the Longest Common Subsequence of prefix $X[0 \dots i-1]$ and prefix $Y[0 \dots j-1]$.
* **Base Case & Initialization:** 
  * Initialize a 2D table `dp` of size $(m + 1) \times (n + 1)$ with zeros (`0`).
  * Set `dp[i][0] = 0` for all $i$ and `dp[0][j] = 0` for all $j$.
* **State Transition:** For each character index $i$ from $1$ to $m$ and $j$ from $1$ to $n$:
  * If $X[i-1] == Y[j-1]$: 
    $$dp[i][j] = dp[i-1][j-1] + 1$$
  * If $X[i-1] \neq Y[j-1]$: 
    $$dp[i][j] = \max(dp[i-1][j], \, dp[i][j-1])$$
* **Reconstruction (Traceback):** Start from `dp[m][n]` and move backwards:
  * If characters match, include the character in the sequence and move diagonally up-left (`i-1`, `j-1`).
  * If they don't match, move toward the direction of the maximum value between `dp[i-1][j]` and `dp[i][j-1]`.

---

## Proper Input Representation
To build a robust and scalable validation program in C:
1. **String Buffers ($X$ and $Y$):** Read dynamic character sequences or strings from standard input.
2. **Dynamic 2D DP Matrix:** Dynamically allocate a 2D array of size $(m + 1) \times (n + 1)$ using `malloc` and `calloc` to prevent static buffer limitations and handle variable-length inputs efficiently.
3. **Dynamic Result Buffer:** Allocate a memory block for the reconstructed LCS string based on the final computed length.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(m \times n)$
  * Where $m$ is the length of sequence $X$ and $n$ is the length of sequence $Y$. The nested loops iterate exactly $(m+1) \times (n+1)$ times to populate the table, and the backtracking phase runs in $\mathcal{O}(m + n)$ time.

* **Space Complexity:** $\mathcal{O}(m \times n)$
  * Auxiliary space is required for the dynamically allocated 2D DP matrix of size $(m + 1) \times (n + 1)$ alongside pointers for input storage.
