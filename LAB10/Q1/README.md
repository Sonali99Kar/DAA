# Lab 10 - Question 1: Online Graph-Bipartiteness Testing

## Overview
This project implements an **Online Graph-Bipartiteness Testing** algorithm in C. A graph is bipartite if and only if it contains no odd-length cycles. In the online setting, edges arrive sequentially one by one. The program maintains whether the graph remains bipartite using a **Disjoint Set Union (DSU)** data structure augmented with **parity tracking**. 

- If adding an edge $(u, v)$ does not introduce an odd cycle, the edge is accepted and added to the disjoint set.
- If adding the edge creates an odd-length cycle, it violates bipartiteness, so the edge is reported and skipped.

---

## Approach & Data Structure
- **Disjoint Set Union (DSU):** Used to efficiently manage connected components.
- **Path Compression & Union by Rank:** Optimizes the `find` and `union` operations for nearly constant-time performance.
- **Parity Array:** An additional `parity[]` array is maintained where:
  - `parity[u] = 0` if vertex $u$ has the same bipartition color as its set representative (root).
  - `parity[u] = 1` if vertex $u$ has the opposite bipartition color relative to its set representative.
- **Cycle Validation:** When an edge $(u, v)$ is processed:
  - If $u$ and $v$ belong to different components, they are unioned, and their relative parity is updated.
  - If $u$ and $v$ belong to the same component and have the **same parity**, adding the edge forms an odd-length cycle (invalid). If they have **different parities**, the edge is consistent with a valid two-coloring.

---

## Complexity Analysis

| Operation | Time Complexity | Explanation |
| :--- | :--- | :--- |
| **Per Edge Query** | $O(\alpha(V))$ | Uses DSU with path compression and union by rank, where $\alpha$ is the Inverse Ackermann function. |
| **Total Time ($E$ Edges)** | $O(E \cdot \alpha(V))$ | Efficient processing for online edge streams. |
| **Space Complexity** | $O(V)$ | Auxiliary storage for `parent[]`, `rank_tree[]`, and `parity[]` arrays of size $V$. |

---

## Getting Started & Compilation

### Prerequisites
You need a standard C compiler (such as `gcc`) installed on your system.

### Compilation
Compile the program using terminal / command prompt:
```bash
gcc -o bipartiteness_test q1.c
