# Lab-08: Question 8 - Optimal Binary Search Trees (OBST)

## Problem Statement
Given a set of $n$ distinct sorted keys $K = \{k_1, k_2, \dots, k_n\}$ with search probabilities $P = \{p_1, p_2, \dots, p_n\}$, and $n+1$ dummy keys $d_0, d_1, \dots, d_n$ representing searches not in $K$ with search probabilities $Q = \{q_0, q_1, \dots, q_n\}$, find the **minimum expected search cost** of a binary search tree.

---

## Algorithm Design (Dynamic Programming)
This problem exhibits optimal substructure and overlapping subproblems, making bottom-up Dynamic Programming the ideal approach:

* **State Definitions:**
  * Let `e[i][j]` represent the optimal expected search cost of a search tree containing keys from $k_i$ through $k_j$.
  * Let `w[i][j]` represent the sum of probabilities for the subtree from index $i$ to $j$:
    $$w[i][j] = w[i, j-1] + p_j + q_j$$
* **Base Cases & Initialization:**
  * When $j = i - 1$ (representing an empty subtree), set $e[i][i-1] = q_{i-1}$ and $w[i][i-1] = q_{i-1}$.
* **State Transition:** For a chain length $l$ from $1$ to $n$, and for each valid start index $i$:
  $$e[i][j] = \min_{i \le r \le j} \{ e[i][r-1] + e[r+1][j] + w[i][j] \}$$
* **Final Result:** The minimum expected search cost for the entire set of keys is stored at `e[1][n]`.

---

## Proper Input Representation
To build a robust and scalable C program for validation:
1. **Number of Keys ($n$):** Read dynamically as an integer to determine the size of the key set.
2. **Probability Arrays ($P$ and $Q$):** Dynamically allocated memory blocks (`malloc`) of size $n+1$ to store key and dummy probabilities accurately.
3. **Dynamic 2D DP Tables:** Allocate auxiliary 2D matrices for `e`, `w`, and `root` of size $(n + 2) \times (n + 2)$ dynamically at runtime to accommodate arbitrary tree sizes without static buffer limitations.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n^3)$
  * There are three nested loops: outer loop for chain length $L$ ($n$ iterations), middle loop for starting index $i$ ($n - L + 1$ iterations), and innermost loop for choosing root $r$ ($L$ iterations). This cubic growth rate is characteristic of classic OBST algorithms.

* **Space Complexity:** $\mathcal{O}(n^2)$
  * $\mathcal{O}(n^2)$ auxiliary memory is required for storing the 2D DP matrices `e`, `w`, and `root` of size $(n+2) \times (n+2)$.
