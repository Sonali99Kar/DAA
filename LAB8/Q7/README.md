# Lab-08: Question 7 - Rod Cutting with Reconstruction

## Problem Statement
Given a rod of length $n$ inches and an array of prices $P = [p_1, p_2, \dots, p_n]$, where $p_i$ denotes the market price of a rod piece of length $i$ inches, determine:
1. The maximum revenue obtainable by cutting up the rod and selling the pieces.
2. The exact lengths of the pieces that constitute the optimal decomposition (reconstruction).
* Cuts are integral and can be made in any combination (including leaving the rod uncut), and the sum of the piece lengths must equal $n$.

---

## Algorithm Design (Dynamic Programming)
This problem exhibits optimal substructure and overlapping subproblems, solved efficiently bottom-up:

* **State Definition:** Let `dp[i]` represent the maximum revenue obtainable for a rod of length $i$.
* **Base Case & Initialization:** 
  * Set `dp[0] = 0` (0 revenue for a rod of length 0).
* **State Transition:** For a rod of length $i$, the maximum revenue is given by:
  $$dp[i] = \max_{1 \le j \le i} (P[j] + dp[i - j])$$
* **Reconstruction (Solution Tracking):** Use a companion array `s[i]` to store the optimal first-piece cut length $j$ that achieves the maximum revenue for a rod of length $i$, allowing us to easily trace back and print the exact piece lengths that make up $n$.

---

## Proper Input Representation
To build a robust and scalable C program for validation:
1. **Rod Length ($n$):** Read dynamically as an integer to determine the size of the rod.
2. **Price Array ($P$):** Dynamically allocated memory block (`malloc`) of size $n$ to store prices for each piece length from 1 to $n$.
3. **Dynamic DP & Solution Tables:** Allocate auxiliary tracking arrays of size $n + 1$ dynamically at runtime to accommodate arbitrary lengths without static buffer limitations.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n^2)$
  * The outer loop runs $n$ times, and the inner loop iterates up to $i$ times for each rod length, leading to a total number of subproblem lookups proportional to $\frac{n(n+1)}{2}$.

* **Space Complexity:** $\mathcal{O}(n)$
  * $\mathcal{O}(n)$ auxiliary memory is used for storing the price array $P$, and $\mathcal{O}(n)$ for the `dp` and solution traceback tracking tables.
