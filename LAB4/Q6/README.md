# Application of Sorting VI: Point of Maximum Interval Overlap

This project uses a sweep-line algorithm running in $\mathcal{O}(n \log n)$ time to find a point $p$ on a line that falls within the largest number of given intervals.

---

## Problem Statement

Given a set $S$ of $n$ line intervals $(l_i, r_i)$, identify a point $p$ covered by the maximum count of intervals (endpoints included).

---

## Algorithmic Strategy

1. **Event Generation ($\mathcal{O}(n)$):** Convert each interval $(l_i, r_i)$ into a start event at $l_i$ (+1) and an end event at $r_i$ (-1).
2. **Tie-Breaker Sorting ($\mathcal{O}(n \log n)$):** Sort all $2n$ events by coordinate value. If coordinates match, process start (+1) events before end (-1) events to ensure inclusive endpoint evaluation.
3. **Line Sweep ($\mathcal{O}(n)$):** Iterate through sorted events, tracking active interval counts and recording coordinate $p$ at maximum overlap.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n \log n)$ — Sorting $2n$ boundary events.
* **Auxiliary Space:** $\mathcal{O}(n)$ — Storage array for $2n$ sweep events.
