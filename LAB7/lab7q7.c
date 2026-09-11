#include <stdio.h>
#include <limits.h>

// Function to print the optimal parenthesization of matrices
void printOptimalParenthesis(int s[100][100], int i, int j, char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");
    printOptimalParenthesis(s, i, s[i][j], name);
    printOptimalParenthesis(s, s[i][j] + 1, j, name);
    printf(")");
}

// Function to solve Matrix Chain Multiplication using Dynamic Programming
void matrixChainOrder(int p[], int n) {
    // m[i][j] stores the minimum number of scalar multiplications
    int m[100][100];
    // s[i][j] stores the optimal split index k
    int s[100][100];

    // Cost is zero when multiplying one matrix
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // L is chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                // q = cost/scalar multiplications
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("--- Matrix Chain Multiplication Results ---\n");
    printf("Minimum number of scalar multiplications: %d\n", m[1][n]);

    printf("Optimal Parenthesization: ");
    char name = 'A';
    printOptimalParenthesis(s, 1, n, &name);
    printf("\n");
}

int main() {
    // Example dimensions: A1 (10x30), A2 (30x55), A3 (55x60) -> p = {10, 30, 55, 60}
    int p[] = {10, 30, 55, 60};
    int n = sizeof(p) / sizeof(p[0]) - 1;

    matrixChainOrder(p, n);

    // Complexity Analysis
    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(n^3) - Due to three nested loops iterating over chain length, starting index, and split point k.\n");
    printf("Space Complexity: O(n^2) - Auxiliary memory for the 2D DP tables m and s.\n");

    return 0;
}