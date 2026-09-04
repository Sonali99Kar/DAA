# DAA Lab 6 - Question 4: Sorting via Reversal Procedure

## Problem Statement
Suppose you are given a permutation $p$ of the integers $1$ to $n$, and seek to sort them in increasing order. The only operation at your disposal is `reverse(p, i, j)`, which reverses the elements of a subsequence $p_i, \dots, p_j$. 
1. Mathematically show that it is possible to sort any permutation using $O(n)$ reversals.
2. Assuming the cost of `reverse(p, i, j)` is equal to its length ($\vert{}j - i\vert{} + 1$), design an algorithm that sorts $p$ in $O(n \log^2 n)$ cost, prove its correctness, and validate it using a C program.

## Part 1: Mathematical Proof for $O(n)$ Reversals
It is possible to sort the array using a **Selection Sort** strategy. 
In each step $i$ (from $1$ to $n$), find the correct element for the $i$-th position from the unsorted portion of the array (from $i$ to $n$). Suppose the correct element is at index $k$. By calling `reverse(p, i, k)`, this element is moved to position $i$.
Since we place exactly one element into its correct sorted position per iteration, we need at most 1 reversal per element. Over $n$ elements, the maximum number of reversals required is $O(n)$.

## Part 2: $O(n \log^2 n)$ Cost Algorithm (In-Place Merge Sort)
Because the cost of a reversal depends on its length, the naive $O(n)$ reversal approach would result in an $O(n^2)$ total cost. To achieve an $O(n \log^2 n)$ cost, the algorithm uses a **Divide and Conquer (In-Place Merge Sort)** approach.

1. **Divide:** Recursively split the array into two halves until base cases of size 1 are reached.
2. **Conquer (In-Place Merge):** Merge two sorted sub-arrays $A$ and $B$ without extra space using block rotations.
   - Pick the median of the larger sub-array as a pivot.
   - Use Binary Search to find the insertion point of the pivot in the other sub-array.
   - Rotate the adjacent blocks (which places the pivot in its globally correct position) using exactly 3 consecutive reversals: `reverse(A); reverse(B); reverse(A+B)`.
   - Recursively merge the remaining left and right segments.

### Complexity Analysis
- **Rotation Cost:** A block rotation of length $L$ using 3 reversals costs $3L$, which is $O(L)$.
- **Merge Cost:** The merge step splits the problem into two subproblems of size at most $\frac{3}{4}n$, with the rotation taking $O(n)$ work. Thus, $T_{merge}(n) = 2T_{merge}(n/2) + O(n) = O(n \log n)$.
- **Total Sort Cost:** The recurrence for the overall sort is $T(n) = 2T(n/2) + T_{merge}(n) = 2T(n/2) + O(n \log n)$. By the Master Theorem, this resolves to **$O(n \log^2 n)$**.

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a standard C compiler (like GCC) installed.

### Compilation
Open your terminal and compile the code:
```bash
gcc q4_reversal_sort.c -o reversal_sort
