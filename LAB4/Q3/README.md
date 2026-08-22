# Application of Sorting III: Generalized $k$-Sum Problem

This project implements an $\mathcal{O}(n^{k-1} \log n)$ algorithm to test whether $k$ distinct elements in a set $S$ add up to a target sum $T$.

---

## Problem Statement

Given a set $S$ of $n$ integers and a target integer $T$, check if there exists a subset of $k$ integers in $S$ whose sum equals $T$.

---

## Algorithmic Strategy

1. **Sort Set $S$ ($\mathcal{O}(n \log n)$):** Sort all $n$ integers in ascending order.
2. **Fix $(k-2)$ Elements ($\mathcal{O}(n^{k-2})$):** Use nested loops (or recursion) to select $k-2$ distinct elements $S[i_1], S[i_2], \dots, S[i_{k-2}]$.
3. **Innermost Search ($\mathcal{O}(n \log n)$):**
   * Iterate through possible choices for the $(k-1)$-th element $S[j]$.
   * Calculate the needed complement: $\text{target} = T - \left(\sum S[i_m] + S[j]\right)$.
   * Use Binary Search to locate the target in the remainder of array $S$.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n^{k-1} \log n)$
  * Array sorting: $\mathcal{O}(n \log n)$
  * Iterating through combinations and searching: $\mathcal{O}(n^{k-2} \cdot n \log n) = \mathcal{O}(n^{k-1} \log n)$
* **Auxiliary Space:** $\mathcal{O}(k)$ recursion call-stack depth and index tracking buffer.
