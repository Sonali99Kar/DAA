#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Structure to represent a graph edge
typedef struct Edge {
    int dest;
    int weight; // 0 or 1
    struct Edge* next;
} Edge;

// Structure to represent an adjacency list
typedef struct {
    Edge* head;
} AdjList;

// Structure for the graph
typedef struct {
    int V;
    AdjList* array;
} Graph;

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Add a directed edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->array[src].head;
    graph->array[src].head = newEdge;
}

// Deque node for 0-1 BFS
typedef struct DequeNode {
    int vertex;
    int parity; // 0 for even, 1 for odd
    struct DequeNode* next;
    struct DequeNode* prev;
} DequeNode;

typedef struct {
    DequeNode* front;
    DequeNode* rear;
} Deque;

Deque* createDeque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->front = dq->rear = NULL;
    return dq;
}

int isEmpty(Deque* dq) {
    return dq->front == NULL;
}

void pushFront(Deque* dq, int vertex, int parity) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->vertex = vertex;
    node->parity = parity;
    node->next = dq->front;
    node->prev = NULL;
    if (dq->front != NULL)
        dq->front->prev = node;
    else
        dq->rear = node;
    dq->front = node;
}

void pushBack(Deque* dq, int vertex, int parity) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->vertex = vertex;
    node->parity = parity;
    node->next = NULL;
    node->prev = dq->rear;
    if (dq->rear != NULL)
        dq->rear->next = node;
    else
    dq->front = node;
    dq->rear = node;
}

DequeNode popFront(Deque* dq) {
    if (isEmpty(dq)) {
        exit(1);
    }
    DequeNode* temp = dq->front;
    DequeNode data = *temp;
    dq->front = dq->front->next;
    if (dq->front != NULL)
        dq->front->prev = NULL;
    else
        dq->rear = NULL;
    free(temp);
    return data;
}

void computeParityShortestPaths(Graph* graph, int S, int C) {
    int V = graph->V;
    
    // dist[v][0] -> min W(P) when k1(P) is even
    // dist[v][1] -> min W(P) when k1(P) is odd
    int** dist = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        dist[i] = (int*)malloc(2 * sizeof(int));
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    Deque* dq = createDeque();

    // Base case: Source vertex S with 0 weight-1 edges (even parity)
    dist[S][0] = 0;
    pushBack(dq, S, 0);

    while (!isEmpty(dq)) {
        DequeNode curr = popFront(dq);
        int u = curr.vertex;
        int p = curr.parity;

        Edge* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            int w = temp->weight;
            int next_p = p ^ w; // Flips parity if edge weight is 1, stays same if 0
            
            int base_dist = dist[u][p];
            if (base_dist != INF) {
                int new_W = base_dist + w;
                if (new_W < dist[v][next_p]) {
                    dist[v][next_p] = new_W;
                    if (w == 0) {
                        pushFront(dq, v, next_p); // 0-weight edge goes to front
                    } else {
                        pushBack(dq, v, next_p);  // 1-weight edge goes to back
                    }
                }
            }
            temp = temp->next;
        }
    }

    // Print final results
    printf("\nVertex\tEven Parity Cost\tOdd Parity Cost\t\tMin Effective Cost (C = %d)\n", C);
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        int cost_even = (dist[i][0] == INF) ? INF : dist[i][0] + 0;
        int cost_odd  = (dist[i][1] == INF) ? INF : dist[i][1] + C;
        
        int min_cost = (cost_even < cost_odd) ? cost_even : cost_odd;

        printf("%d\t", i);
        if (cost_even == INF) printf("Unreachable\t\t");
        else printf("%d\t\t\t", cost_even);

        if (cost_odd == INF) printf("Unreachable\t\t");
        else printf("%d\t\t\t", cost_odd);

        if (min_cost == INF) printf("Unreachable\n");
        else printf("%d\n", min_cost);
    }

    // Clean up memory
    for (int i = 0; i < V; i++) free(dist[i]);
    free(dist);
    free(dq);
}

int main() {
    int V = 4, S = 0, C = 5;
    Graph* graph = createGraph(V);

    // Example graph setup: addEdge(graph, src, dest, weight)
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 2, 0);
    addEdge(graph, 0, 2, 0);
    addEdge(graph, 2, 3, 1);

    printf("Running 0-1 BFS for Parity-Constrained Shortest Path from Source S = %d\n", S);
    computeParityShortestPaths(graph, S, C);

    return 0;
}
