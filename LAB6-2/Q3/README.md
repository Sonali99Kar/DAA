# DAA Lab 6 - Question 3: Convolution Operation on Vectors

## Problem Statement
The convolution of two vectors $A$ (length $m$) and $B$ (length $n$) produces a new vector $C$ of length $m + n - 1$.
Given the standard formula for convolution, design and implement an $O(n \log n)$ divide and conquer algorithm to perform this operation. Assume $n \ge m$. Write a C program to validate the algorithm.

## Approach: Fast Fourier Transform (FFT)
A naive approach using nested loops to compute the convolution directly from the formula takes $O(m \times n)$ or roughly $O(n^2)$ time. To achieve the required $O(n \log n)$ complexity, we use the **Fast Fourier Transform (FFT)**, leveraging the Convolution Theorem (which states that convolution in the time domain equals point-wise multiplication in the frequency domain).

The algorithm involves the following steps:
1. **Padding:** Pad both vectors $A$ and $B$ with zeros so their lengths become equal to the next power of 2 (let's call this length $N$, where $N \ge m + n - 1$).
2. **Forward FFT (Evaluation):** Apply the recursive FFT algorithm to convert both vectors into the frequency domain. This divide-and-conquer step takes $O(N \log N)$ time.
3. **Point-wise Multiplication:** Multiply the frequency representations of $A$ and $B$ element-by-element to create a new frequency domain vector. This takes $O(N)$ time.
4. **Inverse FFT (Interpolation):** Apply the Inverse FFT on the resulting vector to transform it back into the time domain. This yields the final convolved vector $C$, taking $O(N \log N)$ time.

## Complexity Analysis
- **Time Complexity:** $O(N \log N) + O(N) + O(N \log N) = O(N \log N)$. Since $N$ is closely bounded by $2n$, the overall time complexity is strictly **$O(n \log n)$**.
- **Space Complexity:** $O(n)$ — We dynamically allocate arrays of size $N$ (where $N \propto n$) to store the complex number representations of the padded vectors during computation.

## How to Compile and Run (C Program)

### Prerequisites
Ensure you have a C compiler (like GCC) installed. Because the FFT algorithm heavily utilizes complex arithmetic and trigonometric functions, it uses `<complex.h>` and `<math.h>`.

### Compilation
When compiling on a standard Linux/Unix environment, you **must** link the math library using the `-lm` flag:
```bash
gcc q3_convolution.c -o convolution -lm
