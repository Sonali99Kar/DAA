# Quicksort on File Input (`lab5q3.c`)

A C program that generates $N$ random integers, stores them in an input file, sorts them using the **Quicksort** algorithm, and outputs the sorted array to a destination file.

---

## Overview

This program demonstrates file I/O integrated with sorting algorithms in C:
1. Generates $N$ pseudo-random numbers and stores them line-by-line in `input.txt`.
2. Reads the integers into a dynamically allocated array.
3. Sorts the numbers in-place using **Quicksort**.
4. Writes the sorted array into `sorted.txt`.

---

## Quick Start

### Prerequisites

A standard C compiler (e.g., `gcc`, `clang`, or `MSVC`).

### Compilation & Execution

```bash
# Compile lab5q3.c
gcc -O2 lab5q3.c -o lab5q3

# Run the program
./lab5q3
