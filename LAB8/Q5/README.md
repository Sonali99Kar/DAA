# Lab-08: Question 5 - Maximum Sum Increasing Subsequence (MSIS)

## Problem Statement
Given an array of $n$ positive integers $A = [a_0, a_1, \dots, a_{n-1}]$, find the maximum possible sum of a strictly increasing subsequence.

---

## Algorithm Design (Dynamic Programming)
This problem is a natural extension of the Longest Increasing Subsequence (LIS) problem, modified to track cumulative sums instead of lengths:

* **State Definition:** Let `dp[i]` represent the maximum sum of a strictly increasing subsequence ending at index $i$.
* **Base Case & Initialization:** 
  * Initialize every element in the `dp` array to its own value from array $A$ (i.e., `dp[i] = A[i]`), because a single element by itself is an increasing subsequence with a sum equal to that element.
* **State Transition:** For every index $i$ from $1$ to $n-1$, iterate through all previous indices $j$ from $0$ to $i-1$:
  $$\text{If } A[i] > A[j] \text{ and } dp[i] < dp[j] + A[i], \quad dp[i] = dp[j] + A[i]$$
* **Final Result:** The maximum value present in the `dp` array at the end of the iterations represents the maximum sum of a strictly increasing subsequence for the entire array.

---

## Proper Input Representation
To build a robust and scalable validation program in C:
1. **Array Size ($n$):** Read dynamically as an integer to determine the number of elements.
2. **Input Array ($A$):** Dynamically allocated memory block (`malloc`) of size $n$ to store the positive integer elements.
3. **Dynamic DP Table:** Allocate an auxiliary array of size $n$ at runtime to store the maximum increasing sums corresponding to each element index without static buffer limitations.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n^2)$
  * The outer loop runs $n$ times, and the inner loop iterates up to $i$ times for each element, leading to a total number of comparisons proportional to $\frac{n(n-1)}{2}$.

* **Space Complexity:** $\mathcal{O}(n)$
  * $\mathcal{O}(n)$ auxiliary memory is used for dynamically storing the input array $A$ and $\mathcal{O}(n)$ space for the `dp` sum-tracking table.
