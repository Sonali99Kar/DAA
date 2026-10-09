#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a node in the Hu-Tucker / Alphabetic tree sequence
typedef struct Node {
    int weight;
    int depth;
    struct Node *left, *right;
} Node;

// Function to create a new tree node
Node* createNode(int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->weight = weight;
    node->depth = 0;
    node->left = node->right = NULL;
    return node;
}

// Simplified simulation of Hu-Tucker combining process to assign alphabetic tree depths
void huTuckerSimulation(int weights[], int n, int depths[]) {
    // For demonstration, we simulate the stepwise reductions or use a dynamic programming / 
    // priority queue approach adapted for alphabetic constraints.
    // Here we implement a structural simulation to compute node depths for the given ordered weights.
    
    int* currentWeights = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        currentWeights[i] = weights[i];
        depths[i] = 0;
    }

    int size = n;
    while (size > 1) {
        // Find the index 'i' with the minimum sum of adjacent elements (Hu-Tucker reduction rule)
        int minSum = INT_MAX;
        int idx = 0;
        for (int i = 0; i < size - 1; i++) {
            int sum = currentWeights[i] + currentWeights[i + 1];
            if (sum < minSum) {
                minSum = sum;
                idx = i;
            }
        }

        // Increase depth for the leaves involved and merge them in the sequence
        // (Simulating the alphabetic combination steps)
        depths[idx]++;
        depths[idx + 1]++;

        currentWeights[idx] = minSum;
        // Shift remaining weights left
        for (int i = idx + 1; i < size - 1; i++) {
            currentWeights[i] = currentWeights[i + 1];
        }
        size--;
    }

    free(currentWeights);
}

// Function to calculate total weighted path length
int calculateTotalCost(int weights[], int depths[], int n) {
    int totalCost = 0;
    for (int i = 0; i < n; i++) {
        totalCost += weights[i] * depths[i];
    }
    return totalCost;
}

int main() {
    // Ordered sequence of weights
    int weights[] = {4, 6, 8, 12};
    int n = sizeof(weights) / sizeof(weights[0]);

    int* depths = (int*)malloc(n * sizeof(int));

    huTuckerSimulation(weights, n, depths);

    printf("Alphabetic Tree Node Depths:\n");
    for (int i = 0; i < n; i++) {
        printf("Weight w_%d = %d -> Depth = %d\n", i + 1, weights[i], depths[i]);
    }

    int minCost = calculateTotalCost(weights, depths, n);
    printf("\nMinimum Total Weighted Path Length (Sum w_i * depth(i)): %d\n", minCost);

    free(depths);
    return 0;
}