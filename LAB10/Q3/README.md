# Lab 10 - Question 3: Maximum Weight Component with Size Constraints

## Overview
This project implements the **Maximum Weight Component with Size Constraints** algorithm in C. Given an undirected graph where each vertex $v$ has an associated weight $w_v$, edges arrive sequentially. At any point during edge insertions, the program maintains and outputs the maximum total vertex weight among all connected components whose size (number of vertices) does not exceed a given threshold $K$.

---

## Approach & Data Structure
- **Disjoint Set Union (DSU) with Metadata:** We augment the standard DSU data structure to track additional properties for each component:
  - `parent[]`: Stores the representative (root) of each set.
  - `rank_tree[]`: Optimizes tree height during union operations.
  - `comp_size[]`: Tracks the total number of vertices in each connected component.
  - `comp_weight[]`: Tracks the total sum of vertex weights in each connected component.
- **Size Constraint Enforcement ($K$):** 
  - When an edge $(u, v)$ is added, we locate their component roots (`root_u` and `root_v`).
  - If they belong to different components, we check if merging them violates the threshold:
    $$\text{comp\_size}[root\_u] + \text{comp\_size}[root\_v] \le K$$
  - If the combined size exceeds $K$, the merge is skipped. Otherwise, the components are unioned, their weights and sizes are combined, and the global `max_weight` is updated if the new component weight exceeds it.

---

## Complexity Analysis

| Operation | Time Complexity | Explanation |
| :--- | :--- | :--- |
| **Initialization** | $O(V)$ | Initializing DSU arrays and individual vertex weights. |
| **Per Edge Query ($E$ Edges)** | $O(\alpha(V))$ | Each edge query performs DSU `find` operations and constant-time metadata updates. |
| **Total Time Complexity** | $O(V + E \cdot \alpha(V))$ | Highly efficient for dynamic edge streams where $\alpha$ is the Inverse Ackermann function. |
| **Space Complexity** | $O(V)$ | Auxiliary storage for `parent[]`, `rank_tree[]`, `comp_size[]`, `comp_weight[]`, and `vertex_weight[]` arrays of size $V$. |

---

## Getting Started & Compilation

### Prerequisites
A standard C compiler (such as `gcc`).

### Compilation
Compile the program using the terminal / command prompt:
```bash
gcc -o max_weight_component q3.c
