#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159

// Utility function to find the next power of 2 for padding
int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

// Recursive Fast Fourier Transform (FFT) - Divide and Conquer
void fft(double complex *a, int n, int invert) {
    if (n == 1) return;

    // Divide: separate into even and odd indices
    double complex *a0 = malloc(n / 2 * sizeof(double complex));
    double complex *a1 = malloc(n / 2 * sizeof(double complex));
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    // Conquer: recursively apply FFT
    fft(a0, n / 2, invert);
    fft(a1, n / 2, invert);

    // Combine
    double angle = 2 * PI / n * (invert ? -1 : 1);
    double complex w = 1, wn = cos(angle) + I * sin(angle);
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        
        // If performing Inverse FFT, scale the values
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }

    free(a0);
    free(a1);
}

// Function to perform Convolution using FFT
void convolution(double A[], int m, double B[], int n, double result[]) {
    // The resulting vector C will have a size of m + n - 1
    int out_size = m + n - 1;
    
    // Pad to the next power of 2 for FFT
    int N = nextPowerOf2(out_size);

    // Allocate memory for complex arrays and initialize with zeros
    double complex *fa = calloc(N, sizeof(double complex));
    double complex *fb = calloc(N, sizeof(double complex));

    for (int i = 0; i < m; i++) fa[i] = A[i] + 0 * I;
    for (int i = 0; i < n; i++) fb[i] = B[i] + 0 * I;

    // Step 1: Forward FFT on both arrays (O(N log N))
    fft(fa, N, 0);
    fft(fb, N, 0);

    // Step 2: Point-wise multiplication (O(N))
    for (int i = 0; i < N; i++) {
        fa[i] = fa[i] * fb[i];
    }

    // Step 3: Inverse FFT to get the result back in time domain (O(N log N))
    fft(fa, N, 1);

    // Extract real parts as the final convolution result
    for (int i = 0; i < out_size; i++) {
        result[i] = creal(fa[i]);
    }

    free(fa);
    free(fb);
}

int main() {
    // Example Vectors (Polynomials: 1 + 2x + 3x^2 and 4 + 5x + 6x^2 + 7x^3)
    double A[] = {1, 2, 3}; 
    double B[] = {4, 5, 6, 7}; 
    
    int m = sizeof(A) / sizeof(A[0]);
    int n = sizeof(B) / sizeof(B[0]);
    
    int out_size = m + n - 1;
    double *C = malloc(out_size * sizeof(double));

    // Perform Convolution
    convolution(A, m, B, n, C);

    // Print the input vectors
    printf("Vector A: ");
    for(int i = 0; i < m; i++) printf("%.0f ", A[i]);
    
    printf("\nVector B: ");
    for(int i = 0; i < n; i++) printf("%.0f ", B[i]);

    // Print the final convolved vector
    printf("\n\nConvolution Result Vector C (Length %d):\n", out_size);
    for (int i = 0; i < out_size; i++) {
        // Rounding to deal with minor floating-point inaccuracies from FFT arithmetic
        printf("C[%d] = %.0f\n", i, round(C[i]));
    }

    free(C);
    return 0;
}