# Application of Sorting IV: Maximum Simultaneous Attendance

This project provides an $\mathcal{O}(n \log n)$ sweep-line algorithm to analyze party entry/exit timestamps and identify the time when the maximum number of guests were simultaneously present.

---

## Problem Statement

Given $n$ persons $p_i$ with distinct entry times $a_i$ and exit times $b_i$ ($b_i > a_i$), find the time timestamp corresponding to the highest simultaneous attendance.

---

## Algorithmic Strategy

1. **Event Extraction ($\mathcal{O}(n)$):** Represent each guest's entry $a_i$ as an event $(a_i, +1)$ and exit $b_i$ as $(b_i, -1)$, creating $2n$ total events.
2. **Sort Events ($\mathcal{O}(n \log n)$):** Sort all $2n$ events by timestamp in ascending order.
3. **Linear Sweep ($\mathcal{O}(n)$):** Traverse through the sorted events, updating a running tally of active people to find the maximum overlapping point.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n \log n)$ — Sorting $2n$ events dominates the runtime.
* **Auxiliary Space:** $\mathcal{O}(n)$ — Space allocation for $2n$ discrete event records.
