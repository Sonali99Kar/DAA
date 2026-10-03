# Lab-08: Question 6 - Edit Distance with Traceback Information

## Problem Statement
Given two strings $A$ of length $m$ and $B$ of length $n$, compute the minimum number of operations (insertions, deletions, or substitutions) required to transform string $A$ into string $B$, and print the detailed operation traceback.

---

## Algorithm Design (Dynamic Programming)
This is a classic dynamic programming problem (Levenshtein Distance) solved efficiently bottom-up:

* **State Definition:** Let `dp[i][j]` represent the minimum edit distance between prefix $A[0 \dots i-1]$ and prefix $B[0 \dots j-1]$.
* **Base Case & Initialization:** 
  * `dp[i][0] = i` for all $0 \le i \le m$ (transforming a prefix of length $i$ into an empty string requires $i$ deletions).
  * `dp[0][j] = j` for all $0 \le j \le n$ (transforming an empty string into a prefix of length $j$ requires $j$ insertions).
* **State Transition:** For $1 \le i \le m$ and $1 \le j \le n$:
  * If $A[i-1] == B[j-1]$, then:
    $$dp[i][j] = dp[i-1][j-1]$$
  * If $A[i-1] \neq B[j-1]$, then:
    $$dp[i][j] = 1 + \min(\{dp[i-1][j] \text{ (Deletion)}, \; dp[i][j-1] \text{ (Insertion)}, \; dp[i-1][j-1] \text{ (Substitution)}\})$$
* **Traceback (Reconstruction):** Start from `dp[m][n]` and trace back to `dp[0][0]` by inspecting neighboring subproblem costs to determine the exact sequence of edit operations performed.

---

## Proper Input Representation
To build a robust and scalable C program for validation:
1. **String Buffers ($A$ and $B$):** Dynamically allocated memory buffers to handle variable-length strings safely.
2. **Dynamic 2D DP Matrix:** Dynamically allocate a 2D matrix of size $(m + 1) \times (n + 1)$ using `malloc` and `calloc` to avoid static buffer restrictions and efficiently manage memory based on the lengths of input strings.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(m \times n)$
  * Where $m$ is the length of string $A$ and $n$ is the length of string $B$. The nested loops iterate exactly $(m+1) \times (n+1)$ times to populate the table, and the traceback phase runs in $\mathcal{O}(m + n)$ time.

* **Space Complexity:** $\mathcal{O}(m \times n)$
  * $\mathcal{O}(m \times n)$ auxiliary memory is required to store the dynamically allocated 2D DP matrix.
