#include <stdio.h>
#include <stdlib.h>

// Function to allocate dynamic 2D array
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free dynamic 2D array
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Matrix Addition: Result = A + B
void addMatrix(int** A, int** B, int** Result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Recursive Special Pattern Matrix Multiplication
void multiplySpecialMatrix(int** A, int** B, int** C, int n) {
    // Base Case: 1x1 Matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    // Allocate sub-blocks for A and B
    int** A1 = allocateMatrix(half);
    int** A2 = allocateMatrix(half);
    int** B1 = allocateMatrix(half);
    int** B2 = allocateMatrix(half);

    // Extract sub-matrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A1[i][j] = A[i][j];             // Top-left
            A2[i][j] = A[i][j + half];      // Top-right
            B1[i][j] = B[i][j];             // Top-left
            B2[i][j] = B[i][j + half];      // Top-right
        }
    }

    // Allocate intermediate term matrices
    int** A1B1 = allocateMatrix(half);
    int** A2B2 = allocateMatrix(half);
    int** A1B2 = allocateMatrix(half);
    int** A2B1 = allocateMatrix(half);

    int** X = allocateMatrix(half); // X = A1B1 + A2B2
    int** Y = allocateMatrix(half); // Y = A1B2 + A2B1

    // Perform 4 recursive multiplications
    multiplySpecialMatrix(A1, B1, A1B1, half);
    multiplySpecialMatrix(A2, B2, A2B2, half);
    multiplySpecialMatrix(A1, B2, A1B2, half);
    multiplySpecialMatrix(A2, B1, A2B1, half);

    // Compute unique blocks X and Y
    addMatrix(A1B1, A2B2, X, half);
    addMatrix(A1B2, A2B1, Y, half);

    // Assemble final matrix C:
    // [ X  Y ]
    // [ Y  X ]
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j]               = X[i][j]; // Top-Left
            C[i][j + half]        = Y[i][j]; // Top-Right
            C[i + half][j]        = Y[i][j]; // Bottom-Left
            C[i + half][j + half] = X[i][j]; // Bottom-Right
        }
    }

    // Free all dynamically allocated temporary matrices
    freeMatrix(A1, half); freeMatrix(A2, half);
    freeMatrix(B1, half); freeMatrix(B2, half);
    freeMatrix(A1B1, half); freeMatrix(A2B2, half);
    freeMatrix(A1B2, half); freeMatrix(A2B1, half);
    freeMatrix(X, half); freeMatrix(Y, half);
}

int main() {
    int n = 4; // Example dimension (must be 2^k)
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    // Initialize sample symmetric-block values for A and B
    int val = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = val++;
            B[i][j] = val++;
        }
    }

    multiplySpecialMatrix(A, B, C, n);

    printf("Result Matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
    return 0;
}
