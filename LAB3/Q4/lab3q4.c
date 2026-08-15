#include <stdio.h>
#include <stdlib.h>

// Helper function to dynamically allocate a 2D matrix
int** allocateMatrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
    }
    return mat;
}

// Helper function to free allocated memory for a matrix
void freeMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Matrix Addition: Result = A + B
void addMatrix(int** A, int** B, int** Result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Matrix Subtraction: Result = A - B
void subtractMatrix(int** A, int** B, int** Result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's Matrix Multiplication Function
void strassen(int** A, int** B, int** C, int n) {
    // Base Case: 1x1 Matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Sub-matrices for A and B
    int** A11 = allocateMatrix(k);
    int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k);
    int** A22 = allocateMatrix(k);

    int** B11 = allocateMatrix(k);
    int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k);
    int** B22 = allocateMatrix(k);

    // Split matrices A and B into 4 sub-matrices of size (n/2 x n/2)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Temporary matrices for 7 products
    int** P1 = allocateMatrix(k);
    int** P2 = allocateMatrix(k);
    int** P3 = allocateMatrix(k);
    int** P4 = allocateMatrix(k);
    int** P5 = allocateMatrix(k);
    int** P6 = allocateMatrix(k);
    int** P7 = allocateMatrix(k);

    int** T1 = allocateMatrix(k);
    int** T2 = allocateMatrix(k);

    // P1 = (A11 + A22) * (B11 + B22)
    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, P1, k);

    // P2 = (A21 + A22) * B11
    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, P2, k);

    // P3 = A11 * (B12 - B22)
    subtractMatrix(B12, B22, T2, k);
    strassen(A11, T2, P3, k);

    // P4 = A22 * (B21 - B11)
    subtractMatrix(B21, B11, T2, k);
    strassen(A22, T2, P4, k);

    // P5 = (A11 + A12) * B22
    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, P5, k);

    // P6 = (A21 - A11) * (B11 + B12)
    subtractMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, P6, k);

    // P7 = (A12 - A22) * (B21 + B22)
    subtractMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, P7, k);

    // Compute C sub-blocks
    int** C11 = allocateMatrix(k);
    int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k);
    int** C22 = allocateMatrix(k);

    // C11 = P1 + P4 - P5 + P7
    addMatrix(P1, P4, T1, k);
    subtractMatrix(T1, P5, T2, k);
    addMatrix(T2, P7, C11, k);

    // C12 = P3 + P5
    addMatrix(P3, P5, C12, k);

    // C21 = P2 + P4
    addMatrix(P2, P4, C21, k);

    // C22 = P1 - P2 + P3 + P6
    subtractMatrix(P1, P2, T1, k);
    addMatrix(T1, P3, T2, k);
    addMatrix(T2, P6, C22, k);

    // Reconstruct C matrix from sub-blocks
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free memory allocated for temporary matrices
    freeMatrix(A11, k); freeMatrix(A12, k); freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k); freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(C11, k); freeMatrix(C12, k); freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(P1, k); freeMatrix(P2, k); freeMatrix(P3, k); freeMatrix(P4, k);
    freeMatrix(P5, k); freeMatrix(P6, k); freeMatrix(P7, k);
    freeMatrix(T1, k); freeMatrix(T2, k);
}

// Utility function to print matrix
void printMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; // Matrix dimension (n x n, n must be a power of 2)

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    // Sample Matrix A
    int valA[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}
    };

    // Sample Matrix B
    int valB[4][4] = {
        {8, 7, 6, 5},
        {4, 3, 2, 1},
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = valA[i][j];
            B[i][j] = valB[i][j];
        }
    }

    printf("================ Matrix A ================\n");
    printMatrix(A, n);

    printf("\n================ Matrix B ================\n");
    printMatrix(B, n);

    // Execute Strassen's Algorithm
    strassen(A, B, C, n);

    printf("\n==== Result Matrix C (Strassen's D&C) ====\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
