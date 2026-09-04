#include <stdio.h>
#include <stdbool.h>

#define N 3 // Define matrix size for testing

// (i) Matrix Addition: O(n^2)
void addMatrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// (ii) Matrix Multiplication: O(n^3)
void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// (iii) Check if zero matrix: O(n^2)
bool isZeroMatrix(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != 0) return false;
        }
    }
    return true;
}

// (iv) Check if symmetric matrix: O(n^2)
bool isSymmetric(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (A[i][j] != A[j][i]) return false;
        }
    }
    return true;
}

// (v) Compute Determinant (Naive Recursive Approach O(n!))
// Works fine for small matrices like 3x3
int determinant3x3(int A[N][N]) {
    return A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1])
         - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0])
         + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
}

// (vi) Transpose matrix in situ (in place): O(n^2)
void transposeInPlace(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Swap A[i][j] and A[j][i]
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

// Utility function to print a matrix
void printMatrix(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N] = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
    int B[N][N] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // Identity matrix
    int C[N][N]; // To store results

    printf("Matrix A:\n");
    printMatrix(A);

    printf("\n(i) Addition (A + B):\n");
    addMatrices(A, B, C);
    printMatrix(C);

    printf("\n(ii) Multiplication (A * B):\n");
    multiplyMatrices(A, B, C);
    printMatrix(C);

    printf("\n(iii) Is A a zero matrix? %s\n", isZeroMatrix(A) ? "Yes" : "No");
    printf("(iv) Is A a symmetric matrix? %s\n", isSymmetric(A) ? "Yes" : "No");
    printf("(v) Determinant of A (3x3): %d\n", determinant3x3(A));

    printf("\n(vi) Transpose of A (in place):\n");
    transposeInPlace(A);
    printMatrix(A);

    return 0;
}
