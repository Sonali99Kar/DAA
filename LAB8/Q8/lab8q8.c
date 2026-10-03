#include <stdio.h>
#include <stdlib.h>

// Function to compute the Optimal Binary Search Tree minimum cost
void optimalBST(double p[], double q[], int n) {
    // e[i][j] stores the optimal cost, w[i][j] stores the weight sum
    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));
    
    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double *)calloc((n + 2), sizeof(double));
        w[i] = (double *)calloc((n + 2), sizeof(double));
        root[i] = (int *)calloc((n + 2), sizeof(int));
    }
    
    // Base cases
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    
    // L is the chain length
    for (int L = 1; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            e[i][j] = 999999.0;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            
            // Try all keys r from i to j to find the optimal root
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    
    printf("\n--- Results ---\n");
    printf("Number of Keys (n): %d\n", n);
    printf("Minimum Expected Search Cost: %.4f\n", e[1][n]);
    
    // Free allocated memory
    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }
    free(e);
    free(w);
    free(root);
}

int main() {
    int n;
    
    printf("Enter the number of keys (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for number of keys.\n");
        return 1;
    }
    
    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));
    
    if (p == NULL || q == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter search probabilities for keys (p1 to p%d):\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }
    
    printf("Enter search probabilities for dummy keys (q0 to q%d):\n", n);
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }
    
    optimalBST(p, q, n);
    
    free(p);
    free(q);
    return 0;
}