# Lab-08: Question 4 - Longest Increasing Subsequence (LIS)

## Problem Statement
Given an integer array $A = [a_0, a_1, \dots, a_{n-1}]$, find the length of the longest subsequence such that all elements of the subsequence are strictly increasing.

---

## Algorithm Design (Dynamic Programming)
This problem exhibits optimal substructure and overlapping subproblems, making Dynamic Programming the ideal approach:

* **State Definition:** Let `dp[i]` represent the length of the Longest Increasing Subsequence ending at index $i$.
* **Base Case & Initialization:** 
  * Initialize every element in the `dp` array to `1` (since a single element by itself is a valid increasing subsequence of length 1).
* **State Transition:** For every index $i$ from $1$ to $n-1$, iterate through all previous indices $j$ from $0$ to $i-1$:
  $$\text{If } A[i] > A[j], \quad dp[i] = \max(dp[i], \, dp[j] + 1)$$
* **Final Result:** The maximum value present in the `dp` array represents the length of the Longest Increasing Subsequence for the entire array.

---

## Proper Input Representation
To build a robust and scalable validation program in C:
1. **Array Size ($n$):** Read dynamically as an integer to determine the number of elements.
2. **Input Array ($A$):** Dynamically allocated memory block (`malloc`) of size $n$ to store the integer elements.
3. **Dynamic Auxiliary Table:** Allocate a DP tracking array of size $n$ at runtime to accommodate arbitrary array sizes without static buffer limitations.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n^2)$
  * The outer loop runs $n$ times, and the inner loop runs up to $i$ times for each step, resulting in nested iterations proportional to $\frac{n(n-1)}{2}$ comparisons.

* **Space Complexity:** $\mathcal{O}(n)$
  * $\mathcal{O}(n)$ auxiliary memory is used for dynamically storing the input array $A$ and $\mathcal{O}(n)$ space for the `dp` tracking table.
