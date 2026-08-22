# Application of Sorting V: Merge Overlapping Intervals

This project implements a worst-case $\mathcal{O}(n \log n)$ algorithm to merge all overlapping intervals from a given list of intervals.

---

## Problem Statement

Given a list $I$ of $n$ intervals specified as $(x_i, y_i)$ pairs, output a reduced list where all overlapping interval ranges are combined.

---

## Algorithmic Strategy

1. **Sort Intervals ($\mathcal{O}(n \log n)$):** Sort intervals in non-decreasing order based on start coordinate $x_i$.
2. **Sequential Merge Pass ($\mathcal{O}(n)$):** Traverse through intervals sequentially:
   * **Overlap ($x_i \le \text{last.end}$):** Extend current active interval endpoint to $\max(\text{last.end}, y_i)$.
   * **No Overlap ($x_i > \text{last.end}$):** Append $(x_i, y_i)$ as a new interval entry.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n \log n)$ — Driven by sorting $n$ intervals; the merging iteration is linear $\mathcal{O}(n)$.
* **Auxiliary Space:** $\mathcal{O}(n)$ — Buffer array for storing output merged intervals.
