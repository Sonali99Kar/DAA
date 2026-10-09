#include <stdio.h>
#include <stdlib.h>

// Min-Heap structure using long long for safe cost accumulation
typedef struct {
    long long* arr;
    int size;
    int capacity;
} MinHeap;

// Function to create a min-heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (long long*)malloc(capacity * sizeof(long long));
    return heap;
}

// Swap helper
void swap(long long* a, long long* b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heapify up
void minHeapInsert(MinHeap* heap, long long val) {
    if (heap->size == heap->capacity) return;
    int i = heap->size++;
    heap->arr[i] = val;

    while (i != 0 && heap->arr[(i - 1) / 2] > heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Min-Heapify down
void minHeapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;
    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

long long extractMin(MinHeap* heap) {
    if (heap->size <= 0) return -1;
    if (heap->size == 1) return heap->arr[--heap->size];

    long long root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    minHeapify(heap, 0);

    return root;
}

// Function to find the minimum cost to connect sticks
long long connectSticks(int sticks[], int n) {
    if (n <= 1) return 0;

    MinHeap* heap = createMinHeap(n);
    for (int i = 0; i < n; i++) {
        minHeapInsert(heap, sticks[i]);
    }

    long long totalCost = 0;

    // While there is more than one stick in the heap
    while (heap->size > 1) {
        long long first = extractMin(heap);
        long long second = extractMin(heap);

        long long cost = first + second;
        totalCost += cost;

        minHeapInsert(heap, cost);
    }

    free(heap->arr);
    free(heap);
    return totalCost;
}

int main() {
    int sticks[] = {2, 4, 3, 6};
    int n = sizeof(sticks) / sizeof(sticks[0]);

    long long minCost = connectSticks(sticks, n);
    printf("Minimum cost to connect sticks: %lld\n", minCost);

    return 0;
}