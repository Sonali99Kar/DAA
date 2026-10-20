#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100005

int parent[MAX_SIZE];
int rank_tree[MAX_SIZE];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void union_sets(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        if (rank_tree[root_i] < rank_tree[root_j]) {
            parent[root_i] = root_j;
        } else if (rank_tree[root_i] > rank_tree[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank_tree[root_i]++;
        }
    }
}

// Comparison function for qsort (ascending order of integers)
int compare(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}

int main() {
    int n, m;
    printf("Enter number of elements (n) and number of allowable swaps (m): ");
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int A[MAX_SIZE];
    printf("Enter the permutation A (1 to n):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        rank_tree[i] = 0;
    }

    printf("Enter the %d allowable swap pairs (u v) 0-indexed:\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(u, v);
    }

    // Group indices by their DSU root representative
    // To do this simply in C, we can collect indices and values for each root.
    // Given standard lab scale, dynamic grouping or bucket lists can be used.
    
    // Using dynamic arrays or simple index/value extraction per root:
    // For a cleaner competitive/lab approach, we group them using temporary arrays.
    
    int* indices[MAX_SIZE];
    int* values[MAX_SIZE];
    int count[MAX_SIZE] = {0};

    // First pass: count sizes per root
    for (int i = 0; i < n; i++) {
        int root = find(i);
        count[root]++;
    }

    // Allocate memory for each root group
    for (int i = 0; i < n; i++) {
        if (parent[i] == i && count[i] > 0) {
            indices[i] = (int*)malloc(count[i] * sizeof(int));
            values[i] = (int*)malloc(count[i] * sizeof(int));
            count[i] = 0; // reset to use as insertion pointer
        }
    }

    // Second pass: populate indices and values
    for (int i = 0; i < n; i++) {
        int root = find(i);
        indices[root][count[root]] = i;
        values[root][count[root]] = A[i];
        count[root]++;
    }

    // Sort indices and values for each component, then assign back
    for (int i = 0; i < n; i++) {
        if (parent[i] == i && count[i] > 0) {
            qsort(indices[i], count[i], sizeof(int), compare);
            qsort(values[i], count[i], sizeof(int), compare);

            for (int j = 0; j < count[i]; j++) {
                A[indices[i][j]] = values[i][j];
            }

            free(indices[i]);
            free(values[i]);
        }
    }

    printf("\nLexicographically smallest permutation:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}