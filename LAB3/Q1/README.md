# Question 1: Binary Search vs. Ternary Search Analysis

This repository contains the analysis and implementation details for **Question 1** of the Design and Analysis of Algorithms (DAA) Lab-03 assignment.

---

## 📌 Problem Description

In **Binary Search**, a sorted list of $n$ elements is divided into two nearly equal halves, whereas in **Ternary Search**, the list is divided into three nearly equal sub-intervals. Depending on the comparison results at each step, the algorithm recursively or iteratively restricts the search space to one of the identified intervals.

The objective of this task is to:
1. Design and implement a program in **C** to search for an element $x$ in a sorted array of size $n$ using both Binary Search and Ternary Search.
2. Justify and validate mathematically and empirically why **Binary Search is computationally more efficient than Ternary Search**, despite Ternary Search dividing the input space into smaller chunks per step.

---

## 📊 Overview of Theoretical Comparison

While Ternary Search reduces the search space size to $1/3$ per iteration compared to $1/2$ in Binary Search, it requires additional conditional comparisons per iteration level.

* **Binary Search**:
  * Recurrence: $T(n) = T(n/2) + O(1)$
  * Max comparisons per level: **2**
  * Time Complexity: $\Theta(\log_2 n)$

* **Ternary Search**:
  * Recurrence: $T(n) = T(n/3) + O(1)$
  * Max comparisons per level: **4**
  * Time Complexity: $\Theta(\log_3 n)$

### Comparison Overhead

Using logarithmic change of base:
$$\log_3 n = \frac{\log_2 n}{\log_2 3} \approx 0.631 \cdot \log_2 n$$

Evaluating the maximum comparisons in the worst-case scenario:
* **Binary Search Worst Case**: $2 \cdot \log_2 n$ comparisons
* **Ternary Search Worst Case**: $4 \cdot \log_3 n \approx 2.52 \cdot \log_2 n$ comparisons

---

## 🎯 Key Takeaway

Despite making fewer recursive splits overall, **Ternary Search requires $\approx 20\%$ more comparison operations than Binary Search** in the worst case, making Binary Search superior in execution time.
