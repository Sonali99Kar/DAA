#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100005
#define MAX_EDGES 200005

// Graph representation using Adjacency List for edges
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

Node* adj[MAX_VERTICES];

void add_adj_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

int parent[MAX_VERTICES];
int rank_tree[MAX_VERTICES];
long long comp_sum[MAX_VERTICES];
long long vertex_val[MAX_VERTICES];
bool is_active[MAX_VERTICES];
bool deleted_mark[MAX_VERTICES];

int deletion_order[MAX_VERTICES];
long long results[MAX_VERTICES];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

long long max_current_sum = 0;

void union_sets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);

    if (root_u != root_v) {
        if (rank_tree[root_u] < rank_tree[root_v]) {
            parent[root_u] = root_v;
            comp_sum[root_v] += comp_sum[root_u];
            if (comp_sum[root_v] > max_current_sum) {
                max_current_sum = comp_sum[root_v];
            }
        } else if (rank_tree[root_u] > rank_tree[root_v]) {
            parent[root_v] = root_u;
            comp_sum[root_u] += comp_sum[root_v];
            if (comp_sum[root_u] > max_current_sum) {
                max_current_sum = comp_sum[root_u];
            }
        } else {
            parent[root_v] = root_u;
            comp_sum[root_u] += comp_sum[root_v];
            rank_tree[root_u]++;
            if (comp_sum[root_u] > max_current_sum) {
                max_current_sum = comp_sum[root_u];
            }
        }
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices (V) and edges (E): ");
    if (scanf("%d %d", &V, &E) != 2) return 0;

    printf("Enter values of the %d vertices:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%lld", &vertex_val[i]);
        adj[i] = NULL;
        is_active[i] = true;
        deleted_mark[i] = false;
    }

    printf("Enter the %d edges (u v):\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_adj_edge(u, v);
        add_adj_edge(v, u);
    }

    printf("Enter the vertex deletion permutation (V integers):\n");
    for (int i = 0; i < V; i++) {
        scanf("%d", &deletion_order[i]);
        deleted_mark[deletion_order[i]] = true;
    }

    // Initialize DSU for vertices that are NEVER deleted (i.e. initially active in final state)
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank_tree[i] = 0;
        comp_sum[i] = vertex_val[i];
        if (!deleted_mark[i]) {
            is_active[i] = true;
        } else {
            is_active[i] = false; // Will be added in reverse
        }
    }

    // Build the initial graph state containing only vertices never marked in deletion sequence
    for (int u = 0; u < V; u++) {
        if (is_active[u]) {
            Node* temp = adj[u];
            while (temp != NULL) {
                int v = temp->dest;
                if (is_active[v] && u < v) { // avoid duplicate edge processing
                    union_sets(u, v);
                }
                temp = temp->next;
            }
        }
    }

    // Compute initial max_current_sum across active components
    max_current_sum = 0;
    for (int i = 0; i < V; i++) {
        if (is_active[i] && parent[i] == i) {
            if (comp_sum[i] > max_current_sum) {
                max_current_sum = comp_sum[i];
            }
        }
    }

    // Process deletions in reverse order (from step V-1 down to 0)
    for (int step = V - 1; step >= 0; step--) {
        results[step] = max_current_sum;

        int u = deletion_order[step];
        is_active[u] = true;
        
        // Single vertex component check
        if (vertex_val[u] > max_current_sum) {
            max_current_sum = vertex_val[u];
        }

        // Add back its edges to already active neighbors
        Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->dest;
            if (is_active[v]) {
                union_sets(u, v);
            }
            temp = temp->next;
        }
    }

    printf("\nMaximum sum of vertex values after each deletion:\n");
    for (int i = 0; i < V; i++) {
        printf("After deleting vertex %d: Max Component Sum = %lld\n", deletion_order[i], results[i]);
    }

    return 0;
}