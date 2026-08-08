# LAB 2 - Question 1: Dictionary ADT Performance & Empirical Benchmark

## Overview
This program evaluates and benchmarks the asymptotic time complexities for the **7 primary operations** of a Dictionary Abstract Data Type (ADT) across **6 fundamental data structures**:

1. **Unsorted Array**
2. **Sorted Array**
3. **Singly Linked List (Unsorted)**
4. **Singly Linked List (Sorted)**
5. **Doubly Linked List (Unsorted)**
6. **Doubly Linked List (Sorted)**

The C program measures the actual execution time for input sizes ranging from $n = 2000$ to $n = 20000$, outputs performance data files, and automatically plots performance comparison graphs via Gnuplot.

---

## Theoretical Time Complexity

| Data Structure | Search | Insert | Delete | Minimum | Maximum | Predecessor | Successor |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Unsorted Array** | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Sorted Array** | $O(\log n)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| **Singly Linked List (Unsorted)** | $O(n)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Singly Linked List (Sorted)** | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(1)$ |
| **Doubly Linked List (Unsorted)** | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Doubly Linked List (Sorted)** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |

---

## Prerequisites

- **C Compiler:** GCC (MinGW for Windows or native GCC for Linux/macOS)
- **Gnuplot:** Required to render the 6 individual operation graphs automatically upon program completion.

---

## Files Included

- [`lab2q1.c`](https://github.com/Sonali99Kar/DAA/blob/main/LAB2/Q1/lab2q1.c): Main source file containing array/linked list implementations, benchmark loops, data generation, and Gnuplot piping.
- `ds_*.txt`: Benchmark result data files generated at runtime.

---

## How to Compile & Run

### Command Line (GCC)

1. Open your terminal or Command Prompt and navigate to the project directory:
   ```cmd
   cd LAB2/Q1
