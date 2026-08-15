# Question 3: Maximum and Minimum using Divide & Conquer

This repository contains the algorithmic description and theoretical analysis for **Question 3** of the Design and Analysis of Algorithms (DAA) Lab-03 assignment.

---

## 📌 Problem Description

The objective is to find both the maximum and minimum elements in an array of size $n$ using a **Divide and Conquer** approach, ensuring that the total number of comparisons is bounded by $\frac{3n}{2} - 2$.

---

## 💡 Algorithmic Strategy

Instead of scanning linearly (which takes $2n - 2$ comparisons in the worst case):

1. **Base Cases**:
   * If $n = 1$, the single element is both `max` and `min` (0 comparisons).
   * If $n = 2$, compare the two elements once to assign `max` and `min` (1 comparison).
2. **Divide**: Split the array into two equal halves.
3. **Conquer**: Recursively find the (`max`, `min`) of the left and right sub-arrays.
4. **Combine**: Compare the two maximums and two minimums (2 comparisons) to get the overall `max` and `min`.

---

## ⏱️ Comparison Bound Proof

* **Recurrence Relation**: $T(n) = 2T(n/2) + 2$ for $n > 2$.
* **Total Comparisons**:
  * For $n$ being a power of 2, $T(n) = \frac{3n}{2} - 2$.
* **Efficiency**: This reduces the comparison count by $25\%$ compared to the straightforward linear approach.
