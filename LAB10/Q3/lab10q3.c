#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100005

int parent[MAX_VERTICES];
int rank_tree[MAX_VERTICES];
int comp_size[MAX_VERTICES];
long long comp_weight[MAX_VERTICES]; // Total weight of the component
long long vertex_weight[MAX_VERTICES];

long long max_weight = 0;

// Find function with path compression
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Function to add an edge with size constraint K
void add_edge(int u, int v, int K) {
    int root_u = find(u);
    int root_v = find(v);

    if (root_u != root_v) {
        // Check if merging exceeds the size constraint K
        if (comp_size[root_u] + comp_size[root_v] <= K) {
            // Union by rank
            if (rank_tree[root_u] < rank_tree[root_v]) {
                parent[root_u] = root_v;
                comp_size[root_v] += comp_size[root_u];
                comp_weight[root_v] += comp_weight[root_u];
                if (comp_weight[root_v] > max_weight) {
                    max_weight = comp_weight[root_v];
                }
            } else if (rank_tree[root_u] > rank_tree[root_v]) {
                parent[root_v] = root_u;
                comp_size[root_u] += comp_size[root_v];
                comp_weight[root_u] += comp_weight[root_v];
                if (comp_weight[root_u] > max_weight) {
                    max_weight = comp_weight[root_u];
                }
            } else {
                parent[root_v] = root_u;
                comp_size[root_u] += comp_size[root_v];
                comp_weight[root_u] += comp_weight[root_v];
                rank_tree[root_u]++;
                if (comp_weight[root_u] > max_weight) {
                    max_weight = comp_weight[root_u];
                }
            }
        }
    }
}

int main() {
    int V, E, K;
    printf("Enter number of vertices (V), edges (E), and size constraint (K): ");
    if (scanf("%d %d %d", &V, &E, &K) != 3) return 0;

    printf("Enter weights of the %d vertices:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%lld", &vertex_weight[i]);
        parent[i] = i;
        rank_tree[i] = 0;
        comp_size[i] = 1;
        comp_weight[i] = vertex_weight[i];
        
        if (comp_weight[i] > max_weight) {
            max_weight = comp_weight[i];
        }
    }

    printf("Enter the %d edges (u v) one by one:\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        add_edge(u, v, K);

        printf("After edge (%d, %d), Maximum component weight (size <= %d) = %lld\n", u, v, K, max_weight);
    }

    return 0;
}