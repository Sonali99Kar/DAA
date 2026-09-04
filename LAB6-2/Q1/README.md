# DAA Lab 6 - Question 1: 1D Array Operations and Complexities

## Problem Statement
Given an array with $n$ unsorted integer elements, determine the worst-case time complexity for various standard array operations. Implement a C program to validate these procedures and derive the corresponding complexity analysis.

## Implemented Operations & Worst-Case Complexities
The C program implements the following operations on an unsorted array of size $n$. The theoretical worst-case time complexities are:

1.  **Finding the maximum element:** $O(n)$ — Requires a single linear scan.
2.  **Finding the first and second largest elements:** $O(n)$ — Requires a single linear scan tracking the top two values.
3.  **Finding the mean:** $O(n)$ — Requires summing all elements (one pass).
4.  **Finding the median:** $O(n \log n)$ — Requires sorting the array first, then picking the middle element in $O(1)$.
5.  **Finding the standard deviation:** $O(n)$ — Requires finding the mean ($O(n)$) and then a second pass to compute the sum of squared variances ($O(n)$).
6.  **Finding the mode:** $O(n \log n)$ — Requires sorting the array first, followed by a linear scan to find the most frequent consecutive element.
7.  **Removing all duplicates:** $O(n \log n)$ — Requires sorting the array first, then shifting unique elements to the front in $O(n)$.
8.  **Reversing the elements:** $O(n)$ — Requires swapping elements from opposite ends, moving towards the center ($n/2$ swaps).
9.  **Partitioning the array (with a pivot):** $O(n)$ — Requires a two-pointer approach to swap elements less than the pivot to the left, which takes a single pass.

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a C compiler (like GCC) installed on your system.

### Compilation
Because the standard deviation calculation uses the `math.h` library (for `sqrt` and `pow`), you must link the math library during compilation using the `-lm` flag:
```bash
gcc q1_array_operations.c -o array_operations -lm
