# Heap Sort on File Input (`lab5q4.c`)

A C program that generates $N$ random integers, stores them in an input text file, sorts them using the **Heap Sort** algorithm, and writes the sorted array to an output text file.

---

## Overview

This program demonstrates file I/O integrated with the Heap Sort algorithm in C:
1. Generates $N$ pseudo-random integers and writes them line-by-line to `input.txt`.
2. Loads the numbers from the file into a dynamically allocated array.
3. Constructs a **Max-Heap** and performs in-place **Heap Sort**.
4. Saves the sorted dataset to `sorted.txt`.

---

## Features

- **Guaranteed Performance**: Unlike Quicksort, Heap Sort guarantees $O(N \log N)$ execution time regardless of initial data order.
- **In-Place Sorting**: Rearranges elements directly within the existing memory space.
- **File I/O Integration**: Reads input data from disk and writes structured results back to a destination file.

---

## Quick Start

### Prerequisites

A standard C compiler (e.g., `gcc`, `clang`, or `MSVC`).

### Compilation & Execution

```bash
# Compile lab5q4.c
gcc -O2 lab5q4.c -o lab5q4

# Run the program
./lab5q4
