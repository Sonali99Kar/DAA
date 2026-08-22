# Application of Sorting II: Two-Sum Across Sets ($S_1 + S_2 = x$)

This project provides an $\mathcal{O}(n \log n)$ algorithm to determine whether there exists a pair of elements $(a, b)$, where $a \in S_1$ and $b \in S_2$, such that $a + b = x$.

---

## Problem Statement

Given two integer sets $S_1$ and $S_2$ of size $n$, and a target value $x$, find if any element from $S_1$ and any element from $S_2$ sum to $x$.

---

## Algorithmic Strategy

1. **Sort Array $S_1$ ($\mathcal{O}(n \log n)$):** Sort set $S_1$ in ascending order using Quicksort.
2. **Binary Search Pass ($\mathcal{O}(n \log n)$):** Iterate through each element $b \in S_2$. For each $b$, search for target $y = x - b$ in the sorted array $S_1$ using Binary Search ($\mathcal{O}(\log n)$).
3. **Result:** If $y$ is found, return the pair; otherwise, report no match exists.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n \log n)$
  * Sorting $S_1$: $\mathcal{O}(n \log n)$
  * Performing $n$ binary searches: $n \times \mathcal{O}(\log n) = \mathcal{O}(n \log n)$
  * Total Time = $\mathcal{O}(n \log n) + \mathcal{O}(n \log n) = \mathcal{O}(n \log n)$
* **Auxiliary Space:** $\mathcal{O}(1)$ (or $\mathcal{O}(n)$ if operating on a temporary copy of $S_1$).
