#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100005

int parent[MAX_VERTICES];
int rank_tree[MAX_VERTICES];
int parity[MAX_VERTICES]; // parity[u] = 0 if same color as root, 1 if different color

// Find function with path compression and parity tracking
int find(int i) {
    if (parent[i] == i) {
        return i;
    }
    int root = find(parent[i]);
    parity[i] ^= parity[parent[i]]; // Update parity relative to the new root
    return parent[i] = root;
}

// Function to add an edge and check bipartiteness
bool add_edge(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);

    if (root_u == root_v) {
        // If they are in the same component, check if adding an edge 
        // creates an odd cycle (i.e., they have the same parity)
        if (parity[u] == parity[v]) {
            return false; // Violates bipartiteness
        }
        return true; // Already consistent, edge is redundant/valid
    }

    // Union by rank
    if (rank_tree[root_u] < rank_tree[root_v]) {
        parent[root_u] = root_v;
        parity[root_u] = parity[u] ^ parity[v] ^ 1;
    } else if (rank_tree[root_u] > rank_tree[root_v]) {
        parent[root_v] = root_u;
        parity[root_v] = parity[u] ^ parity[v] ^ 1;
    } else {
        parent[root_v] = root_u;
        parity[root_v] = parity[u] ^ parity[v] ^ 1;
        rank_tree[root_u]++;
    }
    return true;
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2) return 0;

    // Initialize DSU
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank_tree[i] = 0;
        parity[i] = 0;
    }

    printf("Enter edges (u v) one by one:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (add_edge(u, v)) {
            printf("Edge (%d, %d) added successfully. Graph remains bipartite.\n", u, v);
        } else {
            printf("Edge (%d, %d) skipped. It violates bipartiteness (creates an odd cycle).\n", u, v);
        }
    }

    return 0;
}