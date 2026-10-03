# Lab-08: Question 2 - Coin Change (Total Number of Ways)

## Problem Statement
Given an array of distinct positive integers representing coin denominations $C = \{c_1, c_2, \dots, c_n\}$ and a target amount $V$, find the total number of distinct combinations of coins that sum up to $V$. 
* Assume an infinite supply of each coin denomination.
* The order of coins does not matter (e.g., $1 + 2$ and $2 + 1$ are considered the same combination).

---

## Algorithm Design (Dynamic Programming)
This is a variation of the unbounded knapsack/subset sum problem, solved efficiently using Dynamic Programming to avoid redundant calculations of overlapping subproblems:

* **State Definition:** Let `dp[i]` represent the total number of distinct combinations to make up the target amount $i$.
* **Base Case & Initialization:** 
  * Initialize an array `dp` of size $V + 1$ with zeros (`0`).
  * Set `dp[0] = 1` (there is exactly 1 way to make an amount of 0: by using no coins at all).
* **State Transition:** For each coin denomination $c_j$ in $C$, iterate through all amounts $i$ from $c_j$ to $V$:
  $$dp[i] = dp[i] + dp[i - c_j]$$
  *(Iterating over the coins in the outer loop ensures that combinations are counted uniquely regardless of order.)*
* **Final Result:** The answer is stored directly in `dp[V]`.

---

## Proper Input Representation
To build a robust and scalable validation program in C:
1. **Coin Array Size ($n$):** Read dynamically as an integer to determine the number of distinct denominations.
2. **Denominations Array ($C$):** Dynamically allocated memory block (`malloc`) of size $n$ to store the individual coin values.
3. **Target Amount ($V$):** Read as a non-negative integer representing the total amount to form combinations for.
4. **Dynamic Auxiliary Table:** Allocate a DP table of size $V + 1$ at runtime to handle arbitrary target amounts without static buffer limitations.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n \times V)$
  * The outer loop runs $n$ times (once for each coin denomination).
  * The inner loop runs $V$ times (from $c_j$ up to $V$).
  * Thus, the total number of operations scales linearly with the product of the number of coins and the target amount.

* **Space Complexity:** $\mathcal{O}(n + V)$
  * $\mathcal{O}(n)$ space is required to dynamically store the coin denominations array $C$.
  * $\mathcal{O}(V)$ auxiliary space is required for the `dp` tracking table of size $V + 1$.
