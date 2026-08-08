# LAB 2 - Question 3: Standard Merge Sort vs. Modified 3-Way Merge Sort

## Overview
This project benchmarks and compares the empirical performance of **Standard Merge Sort (2-Way)** against a **Modified Merge Sort (3-Way)** written in C:

- **Standard Merge Sort (2-Way):** Recursively divides the array into 2 halves, sorts them, and merges them using a standard two-way merge function.
- **Modified Merge Sort (3-Way):** Recursively divides the array into 3 equal segments, sorts each segment, and merges them using a three-way merge subroutine.

The benchmark runs both algorithms over input array sizes ranging from $n = 10,000$ to $n = 100,000$, logs average execution times to a data file, and automatically plots an order-of-growth comparison graph via Gnuplot.

---

## Algorithm Performance Analysis

| Algorithm | Recurrence Relation | Time Complexity | Height of Recursion Tree |
| :--- | :--- | :--- | :--- |
| **Standard Merge Sort (2-Way)** | $T(n) = 2T(n/2) + \Theta(n)$ | $\Theta(n \log_2 n)$ | $\log_2 n$ |
| **Modified Merge Sort (3-Way)** | $T(n) = 3T(n/3) + \Theta(n)$ | $\Theta(n \log_3 n)$ | $\log_3 n$ |

> Both algorithms share the same overall asymptotic time complexity of $\Theta(n \log n)$. While 3-way merge sort reduces the height of the recursion tree from $\log_2 n$ to $\log_3 n$, the additional comparisons required during the 3-way merge step per level balance out the total running time.

---

## Files Included

- [`lab2q3.c`](https://github.com/Sonali99Kar/DAA/blob/main/LAB2/Q3/lab2q3.c): C source file containing implementations for both 2-way and 3-way merge sort, benchmark loops, data logging, and Gnuplot piping.
- `q2_merge_data.txt`: Generated output file containing execution times across varying values of $n$.

---

## Prerequisites

- **C Compiler:** GCC (MinGW for Windows or native GCC for Linux/macOS)
- **Gnuplot:** Required to display the performance graph automatically when running the program.

---

## How to Compile & Run

### Using Command Line (GCC)

1. Open your terminal or Command Prompt and navigate to the `LAB2/Q3` directory:
   ```cmd
   cd LAB2/Q3
