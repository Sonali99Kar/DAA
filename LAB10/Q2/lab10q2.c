#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_GRID_SIZE 1005

int parent[MAX_GRID_SIZE * MAX_GRID_SIZE];
int rank_tree[MAX_GRID_SIZE * MAX_GRID_SIZE];
bool is_land[MAX_GRID_SIZE * MAX_GRID_SIZE];

int R, C;

// Find function with path compression
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Union function returning true if two components were merged
bool union_sets(int i, int j) {
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
        return true; // Successfully merged
    }
    return false; // Already in the same component
}

int main() {
    int K;
    printf("Enter grid rows (R), columns (C), and number of land additions (K): ");
    if (scanf("%d %d %d", &R, &C, &K) != 3) return 0;

    int total_cells = R * C;

    // Initialize DSU and grid states
    for (int i = 0; i < total_cells; i++) {
        parent[i] = i;
        rank_tree[i] = 0;
        is_land[i] = false;
    }

    int island_count = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter the %d land cell coordinates (r c) 0-indexed:\n", K);
    for (int step = 1; step <= K; step++) {
        int r, c;
        scanf("%d %d", &r, &c);

        int idx = r * C + c;

        if (is_land[idx]) {
            printf("Operation %d: Cell (%d, %d) is already land. Current islands: %d\n", step, r, c, island_count);
            continue;
        }

        // Make it land
        is_land[idx] = true;
        island_count++;

        // Check 4-directional neighbors
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                int n_idx = nr * C + nc;
                if (is_land[n_idx]) {
                    if (union_sets(idx, n_idx)) {
                        island_count--; // Merge reduced the island count by 1
                    }
                }
            }
        }

        printf("After adding land at (%d, %d), current number of islands: %d\n", r, c, island_count);
    }

    return 0;
}