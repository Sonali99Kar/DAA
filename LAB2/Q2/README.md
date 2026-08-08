# LAB 2 - Question 2: Standard Merge Sort vs. Modified 3-Way Merge Sort

## Overview
This project analyzes and empirically compares the performance of **Standard Merge Sort (2-way)** against a **Modified Merge Sort (3-way)**:
- **Standard Merge Sort:** Divides the array into 2 halves, recursively sorts each half, and merges them using a 2-way merge function.
- **Modified Merge Sort:** Divides the array into 3 equal thirds, recursively sorts each third, and merges them using a 3-way merge subroutine.

The program benchmarks both implementations across varying array sizes ($n$), logs execution times, and plots their order-of-growth curves to validate the theoretical complexity.

---

## Theoretical Analysis

### Standard Merge Sort (2-Way)
- **Recurrence Relation:** $T(n) = 2T(n/2) + \Theta(n)$
- **Worst-Case Time Complexity:** $O(n \log_2 n)$

### Modified Merge Sort (3-Way)
- **Recurrence Relation:** $T(n) = 3T(n/3) + \Theta(n)$
- **Worst-Case Time Complexity:** $O(n \log_3 n)$

> **Conclusion:** Both algorithms share the same asymptotic growth rate of $\Theta(n \log n)$. While 3-way merge sort reduces the recursion tree height from $\log_2 n$ to $\log_3 n$, the 3-way merge step requires more comparisons per element per level.

---

## Files Included

- [`lab2q2.c`](https://github.com/Sonali99Kar/DAA/tree/main/LAB2/Q2/lab2q2.c): C source code containing implementation of both 2-way and 3-way merge sort, benchmark loops, and Gnuplot script generation.
- `lab2q2.exe`: Compiled executable binary for Windows.

---

## Prerequisites

- **C Compiler:** GCC (MinGW for Windows or native GCC for Linux/macOS)
- **Gnuplot:** Optional, but required for rendering the comparison plots automatically.

---

## How to Compile & Run

### Command Line (GCC)
1. Open your terminal or Command Prompt and navigate to the `LAB2/Q2` directory:
   ```cmd
   cd LAB2/Q2
