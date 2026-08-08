# LAB 2 - Question 3: Merging $k$ Sorted Arrays ($k$-Way Merging Strategies)

## Overview
This project evaluates and empirically compares two distinct strategies for merging $k$ sorted arrays, each containing $n$ elements, into a single sorted array of $kn$ elements:

- **Method 1 (Iterative Sequential Merge):** Sequentially merges arrays one by one into an accumulating sorted array using standard two-way merging.
- **Method 2 (Divide & Conquer / Tree-Based Merge):** Pairs up arrays and merges them pairwise iteratively (similar to a merge sort tree structure) until a single array remains.

The C program measures actual execution times for both algorithms across varying parameters of $k$ and $n$, outputs empirical benchmark data, and plots order-of-growth performance graphs.

---

## Theoretical Analysis & Time Complexity

### Method 1: Sequential Merging
- **Process:** Merges Array 1 and 2 ($2n$), then merges the result with Array 3 ($3n$), repeating up to $k$ arrays.
- **Total Comparisons:** $\sum_{i=2}^{k} i \cdot n = n \left( \frac{k(k+1)}{2} - 1 \right)$
- **Worst-Case Running Time:** $O(k^2 n)$

### Method 2: Pairwise Divide & Conquer Merging
- **Process:** Merges $\frac{k}{2}$ pairs in level 1, $\frac{k}{4}$ pairs in level 2, across $\lceil \log_2 k \rceil$ recursion levels. Each level processes a total of $kn$ elements across all merges.
- **Total Comparisons:** $O(kn \log k)$
- **Worst-Case Running Time:** $O(kn \log k)$

> **Conclusion:** Method 2 significantly outperforms Method 1 as $k$ grows large due to its logarithmic reduction in merge pass depth ($O(kn \log k)$ vs. $O(k^2 n)$).

---

## Files Included

- [`lab2q3.c`](https://github.com/Sonali99Kar/DAA/tree/main/LAB2/Q3/blob/main/LAB2/Q3/lab2q3.c): C source file containing implementations for both merging strategies, array generation, timing benchmarks, and Gnuplot script execution.
- `lab2q3.exe`: Compiled binary executable.

---

## Prerequisites

- **C Compiler:** GCC (MinGW for Windows or native GCC for Linux/macOS)
- **Gnuplot:** Optional, required for generating visual comparison plots automatically upon execution.

---

## How to Compile & Run

### Command Line (GCC)

1. Open your terminal or Command Prompt and navigate to the `LAB2/Q3` directory:
   ```cmd
   cd LAB2/Q3
