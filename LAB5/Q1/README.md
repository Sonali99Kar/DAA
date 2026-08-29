# Quickselect Median Finder (`lab5q1.c`)

An efficient, in-place C implementation to find the median of an unsorted array without fully sorting it, using the **Quickselect** algorithm (Hoare's selection algorithm).

---

## Overview

Sorting an array to find the median takes $O(n \log n)$ time complexity. By using **Quickselect**, `lab5q1.c` finds the median in **$O(n)$ average time complexity** and $O(1)$ auxiliary memory by repeatedly partitioning the array around a pivot and ignoring the partition that does not contain the target median index.

---

## Features

- **No full sorting needed**: Only partitions the subset of the array that contains the median.
- **Handles both odd and even array lengths**:
  - **Odd length**: Returns the exact middle element at index $n / 2$.
  - **Even length**: Returns the average of the two middle elements at indices $(n / 2) - 1$ and $n / 2$.
- **In-place partition**: Operates directly on the input array with zero dynamic memory allocation.

---

## Quick Start

### Prerequisites

A C compiler such as `gcc`, `clang`, or `MSVC`.

### Compilation & Execution

```bash
# Compile lab5q1.c
gcc -O2 lab5q1.c -o lab5q1

# Run the executable
./lab5q1
