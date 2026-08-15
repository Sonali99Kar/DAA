# Question 6: Loop Invariants in Selection Sort Analysis

This repository contains the loop invariant proof and complexity analysis for **Question 6** of the Design and Analysis of Algorithms (DAA) Lab-03 assignment.

---

## 📌 Problem Description

Analyze Selection Sort on an array $A[1 \dots n]$, where the smallest element in $A[i \dots n]$ is repeatedly swapped into position $i$ for $i = 1$ to $n-1$.

---

## 🔍 Loop Invariant

**Invariant Statement**: At the start of each iteration $i$ of the outer loop, the sub-array $A[1 \dots i-1]$ contains the $(i-1)$ smallest elements of the array in sorted order.

### Proof of Correctness
* **Initialization**: For $i = 1$, $A[1 \dots 0]$ is empty, which is trivially sorted.
* **Maintenance**: Finding the minimum in $A[i \dots n]$ and placing it at $A[i]$ ensures $A[1 \dots i]$ contains the $i$ smallest elements in sorted order.
* **Termination**: The loop terminates at $i = n$. By the invariant, $A[1 \dots n-1]$ is sorted and contains the $n-1$ smallest elements. Consequently, $A[n]$ must contain the largest remaining element, making the entire array sorted.

---

## ⏱️ Complexity Analysis

* Why run for $n-1$ elements? Once the first $n-1$ elements are placed in their correct positions, the last element $A[n]$ is automatically in its correct position.
* **Worst-case Time Complexity**: $\Theta(n^2)$ (requires $\frac{n(n-1)}{2}$ comparisons).
* **Best-case Time Complexity**: $\Theta(n^2)$ (Selection Sort still scans the remaining unsorted sub-array to verify the minimum even if the array is already sorted).
