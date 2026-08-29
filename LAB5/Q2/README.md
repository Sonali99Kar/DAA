# K-th Smallest Element Finder (`lab5q2.c`)

An efficient, in-place C implementation to find the $k$-th smallest element in an unsorted array of $n$ numbers without sorting the entire array, using the **Quickselect** algorithm.

---

## Overview

Sorting an array to find the $k$-th smallest element requires $O(n \log n)$ time. By using **Quickselect** (Hoare's Selection Algorithm), `lab5q2.c` locates the target element in **$O(n)$ average time complexity** and $O(1)$ auxiliary space. It achieves this by partitioning the array around a pivot and recursing only into the partition containing the target index $k - 1$.

---

## Features

- **No full sorting needed**: Only rearranges elements in the subarray containing the $k$-th target index.
- **1-Based Indexing Support**: Easily queries for $k$-th position (e.g., $k=1$ for minimum, $k=n$ for maximum).
- **In-place partition**: Uses Lomuto's partitioning scheme with zero dynamic memory allocation.

---

## Quick Start

### Prerequisites

A C compiler such as `gcc`, `clang`, or `MSVC`.

### Compilation & Execution

```bash
# Compile lab5q2.c
gcc -O2 lab5q2.c -o lab5q2

# Run the executable
./lab5q2
