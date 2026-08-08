 # LAB 2 - Question 3: Merging $k$ Sorted Arrays ($k$-Way Merging Strategies)

## Overview
This project benchmarks and empirically validates two strategies for combining $k$ sorted arrays, each of size $n$, into a single fully sorted array of $kn$ elements:

1. **Method 1 (Iterative Sequential Merging):** Iteratively merges arrays one by one into an accumulating output array using standard two-way merging.
2. **Method 2 (Pairwise Divide & Conquer Merging):** Pairs up adjacent arrays and merges them in logarithmic passes using a tree-like merge structure.

The C program records execution times across varying numbers of arrays ($k$), writes benchmark data to a text file, and plots an order-of-growth comparison graph using Gnuplot.

---

## Theoretical Complexity & Analysis

### Method 1: Iterative Sequential Merging
- **Process:** Merges Array 1 and 2 ($2n$), then the result with Array 3 ($3n$), up to Array $k$ ($kn$).
- **Total Comparisons:** $\sum_{i=2}^{k} i \cdot n = O(k^2 n)$
- **Worst-Case Running Time:** $O(k^2 n)$

### Method 2: Pairwise Divide & Conquer Merging
- **Process:** Pairs up and merges $k$ arrays into $\frac{k}{2}$ arrays of size $2n$, repeating across $\lceil \log_2 k \rceil$ merge passes. Each pass processes $kn$ total elements.
- **Total Comparisons:** $O(kn \log k)$
- **Worst-Case Running Time:** $O(kn \log k)$

> **Conclusion:** Method 2 dramatically outperforms Method 1 as $k$ grows because it reduces the depth of the merge passes from linear ($O(k)$ passes) to logarithmic ($O(\log k)$ passes).

---

## Files Included

- [`lab2q3.c`](https://github.com/Sonali99Kar/DAA/blob/main/LAB2/Q3/lab2q3.c): C source file implementing both $k$-way array merge algorithms, benchmark loops, and Gnuplot script execution.
- `q3_merge_data.txt`: Generated benchmark output file storing execution times for varying values of $k$.

---

## Prerequisites

- **C Compiler:** GCC (MinGW for Windows or native GCC for Linux/macOS)
- **Gnuplot:** Required to render the graph automatically upon running the compiled binary.

---

## How to Compile & Run

### Using Command Line (GCC)

1. Open your terminal or Command Prompt and navigate to the `LAB2/Q3` directory:
   ```cmd
   cd LAB2/Q3
