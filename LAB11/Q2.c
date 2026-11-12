#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Structure for adjacency list node
typedef struct Edge {
    int dest;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} AdjList;

typedef struct {
    int V;
    AdjList* array;
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Add an undirected edge
void addUndirectedEdge(Graph* graph, int src, int dest) {
    // Add src to dest
    Edge* edge1 = (Edge*)malloc(sizeof(Edge));
    edge1->dest = dest;
    edge1->next = graph->array[src].head;
    graph->array[src].head = edge1;

    // Add dest to src
    Edge* edge2 = (Edge*)malloc(sizeof(Edge));
    edge2->dest = src;
    edge2->next = graph->array[dest].head;
    graph->array[dest].head = edge2;
}

// Queue structure for standard BFS
typedef struct QueueNode {
    int vertex;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int vertex) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->vertex = vertex;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    QueueNode* temp = q->front;
    int vertex = temp->vertex;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return vertex;
}

void computeVoronoiPartition(Graph* graph, int* hubs, int K, int R) {
    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    int* owner = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        owner[i] = -1;
    }

    Queue* q = createQueue();

    // Initialize Multi-Source BFS with all hubs
    // Note: Hubs array is 0-indexed in code, but hub IDs are typically 1-indexed. 
    // We store hub index as (i + 1).
    for (int i = 0; i < K; i++) {
        int h = hubs[i];
        int hub_id = i + 1;
        
        if (dist[h] == INF) {
            dist[h] = 0;
            owner[h] = hub_id;
            enqueue(q, h);
        } else {
            // If multiple hubs start at the same node, apply tie-breaking (smaller index wins)
            if (dist[h] == 0 && hub_id < owner[h]) {
                owner[h] = hub_id;
            }
        }
    }

    // BFS Traversal
    while (!isQueueEmpty(q)) {
        int u = dequeue(q);

        // If distance exceeds threshold R, we can stop expanding further from this node
        if (dist[u] >= R) continue;

        Edge* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            int new_dist = dist[u] + 1;

            if (new_dist <= R) {
                if (dist[v] == INF) {
                    dist[v] = new_dist;
                    owner[v] = owner[u];
                    enqueue(q, v);
                } else if (dist[v] == new_dist) {
                    // Tie-breaking rule: Choose the hub with the smaller numerical index
                    if (owner[u] < owner[v]) {
                        owner[v] = owner[u];
                    }
                }
            }
            temp = temp->next;
        }
    }

    // Final Post-processing for threshold R rule check
    for (int i = 0; i < V; i++) {
        if (dist[i] > R) {
            owner[i] = -1;
        }
    }

    // Print Results
    printf("\nVertex (v)\tAssigned Owner (Hub Index)\tShortest Distance (d_min)\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t\t", i);
        if (owner[i] == -1) {
            printf("Unassigned (-1)\t\t\t");
            if (dist[i] == INF) printf("Unreachable (INF)\n");
            else printf("%d (Exceeds R=%d)\n", dist[i], R);
        } else {
            printf("Hub %d\t\t\t\t%d\n", owner[i], dist[i]);
        }
    }

    // Clean up memory
    free(dist);
    free(owner);
    free(q);
}

int main() {
    int V = 6; // Vertices 0 to 5
    Graph* graph = createGraph(V);

    // Constructing an undirected graph
    addUndirectedEdge(graph, 0, 1);
    addUndirectedEdge(graph, 1, 2);
    addUndirectedEdge(graph, 2, 3);
    addUndirectedEdge(graph, 0, 4);
    addUndirectedEdge(graph, 4, 5);
    addUndirectedEdge(graph, 5, 3);
    addUndirectedEdge(graph, 1, 4); // Creates multiple paths

    // Designated hubs (0-indexed vertex values)
    // Hub 1 is at vertex 0, Hub 2 is at vertex 3
    int hubs[] = {0, 3};
    int K = 2;
    int R = 2; // Radius threshold

    printf("Running Multi-Source BFS for Voronoi Cell Partitioning (K = %d, R = %d)\n", K, R);
    computeVoronoiPartition(graph, hubs, K, R);

    return 0;
}
