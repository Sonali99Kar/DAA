# DAA Lab 6 - Question 2: 2D Square Matrix Operations and Complexities

## Problem Statement
Given square matrices with $n$ rows and $n$ columns, determine the worst-case computational complexity for various standard matrix algorithms in terms of $n$. Implement a C program to validate these procedures and derive the corresponding complexity analysis.

## Implemented Operations & Worst-Case Complexities
The C program implements several fundamental operations on $n \times n$ matrices. The theoretical worst-case time complexities are:

1.  **Matrix Addition:** $O(n^2)$ — Requires iterating through all $n \times n$ elements to add corresponding entries.
2.  **Matrix Multiplication:** $O(n^3)$ — The standard naive approach requires three nested loops to compute the dot products for each cell in the resulting matrix.
3.  **Finding if the given matrix is a zero matrix:** $O(n^2)$ — In the worst case (e.g., a zero matrix or a matrix where only the very last element is non-zero), we must check all $n^2$ elements.
4.  **Finding if the given matrix is a symmetric matrix:** $O(n^2)$ — Requires checking if $A[i][j] == A[j][i]$. Although we only need to check the upper or lower triangle ($\approx n^2 / 2$ checks), the asymptotic complexity remains $O(n^2)$.
5.  **Computing the determinant:** $O(n!)$ for naive recursive approach (Laplace expansion), or $O(n^3)$ using Gaussian Elimination/LU Decomposition. (The provided C program implements the naive approach suitable for a small $3 \times 3$ matrix).
6.  **Transposing the matrix in situ (in place):** $O(n^2)$ — Requires swapping elements across the main diagonal ($n^2 / 2$ swaps), dropping the constant gives $O(n^2)$.
7.  **Finding eigenvalues and eigenvectors:** $O(n^3)$ — Standard numerical methods like the QR algorithm generally take $O(n^3)$ per iteration. *(Note: Typically requires advanced numerical libraries, so standard structural operations are prioritized in the C implementation).*

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a standard C compiler (like GCC) installed on your system.

### Compilation
Open your terminal and compile the code using the following command:
```bash
gcc q2_matrix_operations.c -o matrix_operations
