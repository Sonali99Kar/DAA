# Lab 10 - Question 5: Lexicographically Smallest Connected Component Permutation

## Overview
This project implements the **Lexicographically Smallest Connected Component Permutation** algorithm in C. Given a permutation $A$ of numbers from $1$ to $n$ and a set of allowable pairwise swaps $(u, v)$ (which form edges in an undirected graph), the goal is to find the lexicographically smallest permutation achievable through any number of valid swaps.

---

## Approach & Data Structure
- **Disjoint Set Union (DSU):** 
  - Each index $0$ to $n-1$ represents a vertex. 
  - Each allowable swap $(u, v)$ is used to perform a `union` operation, grouping indices that can reach each other into the same connected component.
- **Component Extraction & Sorting:**
  - For each connected component, we collect all the **indices** belonging to that component and all the **values** currently residing at those indices in permutation $A$.
  - We sort both the indices in ascending order and the values in ascending order.
  - To achieve the lexicographically smallest arrangement, we greedily place the smallest available values into the smallest available indices within each connected component.

---

## Complexity Analysis

| Operation | Time Complexity | Explanation |
| :--- | :--- | :--- |
| **DSU Initialization & Swaps ($M$ Pairs)** | $O(n + m \cdot \alpha(n))$ | Processing $m$ allowable swap pairs using DSU with path compression and union by rank. |
| **Grouping & Sorting Component Elements** | $O(n \log n)$ | Collecting indices and values, followed by sorting each component. Across all components, sorting takes at most $O(n \log n)$ time. |
| **Total Time Complexity** | $O(n \log n + m \cdot \alpha(n))$ | Highly efficient for large permutations and swap constraints. |
| **Space Complexity** | $O(n)$ | Auxiliary storage for DSU arrays (`parent[]`, `rank_tree[]`) and dynamic component buffers of size $n$. |

---

## Getting Started & Compilation

### Prerequisites
A standard C compiler (such as `gcc`).

### Compilation
Compile the program using the terminal / command prompt:
```bash
gcc -o smallest_permutation q5.c
