# Lab 10 - Question 4: Reverse Time-Step DSU Application

## Overview
This project implements the **Reverse Time-Step DSU Application** algorithm in C. Given a vertex-weighted undirected graph, vertices are sequentially deleted one by one in a given order $P = [p_1, p_2, \dots, p_V]$. After each vertex deletion, the program computes and outputs the maximum sum of vertex values among all remaining connected components. 

Since deleting vertices and incident edges online is inefficient using standard DSU, this program uses the efficient **offline reverse time-step** (or time-reversal) technique.

---

## Approach & Data Structure
- **Offline Time-Reversal:** Instead of deleting vertices forward in time, we read all initial vertices, edges, and the entire deletion permutation first. We then start from the final graph state (where specified vertices are removed) and process the deletion sequence **in reverse order** (from the last deleted vertex back to the first).
- **Disjoint Set Union (DSU) with Metadata:** 
  - `parent[]` and `rank_tree[]`: Standard DSU arrays with path compression and union by rank.
  - `comp_sum[]`: Tracks the sum of vertex values in each connected component.
  - `is_active[]`: A boolean tracking array indicating whether a vertex is currently present in the graph.
- **Reverse Insertion:** As each vertex is "added back" in reverse chronological order along with its incident edges to already active neighbors, components are merged, and a running global `max_current_sum` is efficiently updated. The results are then stored and printed in the original chronological order of deletions.

---

## Complexity Analysis

| Operation | Time Complexity | Explanation |
| :--- | :--- | :--- |
| **Initialization & Graph Setup** | $O(V + E)$ | Reading vertices, weights, adjacency list, and deletion permutation. |
| **Building Final Graph State** | $O(E \cdot \alpha(V))$ | Initial union operations for vertices and edges present in the final state. |
| **Reverse Traversal ($V$ deletions)** | $O((V + E) \cdot \alpha(V))$ | Each vertex and its incident edges are processed once across the reverse timeline using DSU `find` and `union`. |
| **Total Time Complexity** | $O((V + E) \cdot \alpha(V))$ | Highly efficient compared to a naive $O(V \cdot (V + E))$ forward simulation. |
| **Space Complexity** | $O(V + E)$ | Storage for adjacency list ($O(V + E)$) and DSU arrays (`parent[]`, `comp_sum[]`, `vertex_val[]`, etc. of size $V$). |

---

## Getting Started & Compilation

### Prerequisites
A standard C compiler (such as `gcc`).

### Compilation
Compile the program using the terminal / command prompt:
```bash
gcc -o reverse_dsu q4.c
