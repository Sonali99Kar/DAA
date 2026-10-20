# Lab 10 - Question 2: Dynamic Connected Components in a Grid (Number of Islands II)

## Overview
This project implements the **Dynamic Connected Components in a Grid** algorithm (commonly known as *Number of Islands II*) in C. 
- The grid of size $R \times C$ starts completely filled with water (`false`).
- Land cells are added sequentially one by one at specified coordinates $(r, c)$.
- After each land addition operation, the program efficiently computes and outputs the current number of 4-directionally connected land components (islands) using a **Disjoint Set Union (DSU)** data structure with **coordinate flattening**.

---

## Approach & Data Structure
- **Coordinate Flattening:** A 2D grid cell at row $r$ and column $c$ is mapped into a unique 1D index using row-major ordering:
  $$\text{index} = r \times C + c$$
- **Disjoint Set Union (DSU):** Maintains connected components of land cells using:
  - `parent[]`: Stores the representative (root) of each set.
  - `rank[]`: Optimizes tree height during union operations.
  - `is_land[]`: A boolean status array tracking whether a cell has been activated as land.
- **Dynamic Updates:** 
  - When a new land cell is added, we check its 4-directional neighbors (up, down, left, right).
  - For each neighboring cell that is already land, we perform a DSU `find` and `union`.
  - Every successful merge between two separate components reduces the total island count by 1.

---

## Complexity Analysis

| Operation | Time Complexity | Explanation |
| :--- | :--- | :--- |
| **Grid Initialization** | $O(R \times C)$ | Allocating and initializing DSU arrays and grid states. |
| **Per Land Addition ($K$ ops)** | $O(\alpha(R \times C))$ | Each addition checks 4 constant neighbors, performing DSU `find` and `union` operations with path compression. |
| **Total Time Complexity** | $O(R \times C + K \cdot \alpha(R \times C))$ | Highly efficient for dynamic grid streams where $\alpha$ is the Inverse Ackermann function. |
| **Space Complexity** | $O(R \times C)$ | Auxiliary storage for `parent[]`, `rank_tree[]`, and `is_land[]` arrays of size $R \times C$. |

---

## Getting Started & Compilation

### Prerequisites
A standard C compiler (such as `gcc`).

### Compilation
Compile the program using the terminal / command prompt:
```bash
gcc -o dynamic_islands q2.c
