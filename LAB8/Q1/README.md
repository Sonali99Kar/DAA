# Lab-08: Question 1 - Minimum Coin Change

## Problem Statement
Given an integer array of coin denominations $C = \{c_1, c_2, \dots, c_n\}$ representing coins of different values, and an integer target amount $V$, find the minimum number of coins needed to make up that amount. 
* Assume an infinite supply of each coin denomination.
* If that amount of money cannot be made up by any combination of the coins, return `-1`.

---

## Algorithm Design (Dynamic Programming)
This problem exhibits optimal substructure and overlapping subproblems, making Dynamic Programming the ideal approach:

* **State Definition:** Let `dp[i]` represent the minimum number of coins required to make up the target amount $i$.
* **Base Case & Initialization:** 
  * Initialize an array `dp` of size $V + 1$ with a sentinel value representing infinity ($\infty$).
  * Set `dp[0] = 0` (0 coins are needed to make an amount of 0).
* **State Transition:** For each amount $i$ from $1$ to $V$, and for each coin denomination $c_j$ in $C$:
  $$\text{If } c_j \le i, \quad dp[i] = \min(dp[i], \, dp[i - c_j] + 1)$$
* **Final Result:** Check the value at `dp[V]`. If it remains $\infty$, return `-1`; otherwise, return `dp[V]`.

---

## Proper Input Representation
To build a robust and scalable validation program in C:
1. **Coin Array Size ($n$):** Read dynamically as an integer to determine the number of denominations.
2. **Denominations Array ($C$):** Dynamically allocated memory block (`malloc`) of size $n$ to store the individual coin values.
3. **Target Amount ($V$):** Read as a non-negative integer representing the total amount to form.
4. **Dynamic Auxiliary Table:** Allocate a DP table of size $V + 1$ at runtime to accommodate arbitrary target amounts efficiently without static buffer limitations.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n \times V)$
  * The outer loop runs $V$ times (from $1$ to $V$).
  * The inner loop iterates through all $n$ coin denominations.
  * Thus, the total operations scale linearly with the product of the number of coins and the target amount.

* **Space Complexity:** $\mathcal{O}(n + V)$
  * $\mathcal{O}(n)$ space is required to dynamically store the coin denominations array $C$.
  * $\mathcal{O}(V)$ auxiliary space is required for the `dp` tracking table of size $V + 1$.
