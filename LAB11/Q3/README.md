# Shortest Transformation Sequence in a Word Graph (Bidirectional BFS)

This project contains a C implementation to solve **Question 3: Bidirectional BFS for Shortest Transformation Sequence in a Word Graph** from the Design and Analysis of Algorithms (DAA) Lab-11 assignment.

## Problem Overview

Given a dictionary $D$ containing $N$ unique words of identical length $L$, a starting word $A$, and a target word $B$, the objective is to find the **minimum number of mutations $k$** required to transform $A$ into $B$. 

* **Valid Mutation:** Changing exactly one character of a word such that the resulting intermediate word exists in the dictionary $D$.
* **Constraints:**
  * Number of dictionary words: $N \le 10^5$
  * Word length: $L \le 10$
  * Character set: Lowercase English letters ('a' to 'z').

---

## Algorithm & Approach: Bidirectional Breadth-First Search (BFS)

To efficiently handle the large search space ($N \le 10^5$ and $L \le 10$), standard BFS from a single source can become too slow. Instead, we use **Bidirectional BFS**:
1. We maintain two search frontiers: one starting forward from $A$ and one starting backward from $B$.
2. In each step, we expand the smaller queue to maintain balanced search depths and avoid explosive branching factors.
3. If the two search frontiers intersect, we have found the shortest transformation sequence.

---
