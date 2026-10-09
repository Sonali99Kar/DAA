#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Max-Heap structure
typedef struct {
    int* arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapInsert(MaxHeap* heap, int val) {
    if (heap->size == heap->capacity) return;
    int i = heap->size++;
    heap->arr[i] = val;

    while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void maxHeapify(MaxHeap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left] > heap->arr[largest])
        largest = left;
    if (right < heap->size && heap->arr[right] > heap->arr[largest])
        largest = right;

    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        maxHeapify(heap, largest);
    }
}

int extractMax(MaxHeap* heap) {
    if (heap->size <= 0) return -1;
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    maxHeapify(heap, 0);
    return root;
}

// Function to find minimum deviation
int minimumDeviation(int nums[], int n) {
    MaxHeap* maxHeap = createMaxHeap(n);
    int minVal = INT_MAX;

    // Step 1: Normalize all numbers to be as large as possible
    for (int i = 0; i < n; i++) {
        int val = nums[i];
        if (val % 2 != 0) {
            val *= 2; // Multiply odd numbers by 2
        }
        maxHeapInsert(maxHeap, val);
        if (val < minVal) {
            minVal = val; // Track the minimum element in the heap
        }
    }

    int minDeviation = INT_MAX;

    // Step 2: Greedily reduce the maximum element
    while (1) {
        int maxVal = extractMax(maxHeap);
        
        // Update minimum deviation found so far
        int currentDeviation = maxVal - minVal;
        if (currentDeviation < minDeviation) {
            minDeviation = currentDeviation;
        }

        // If the current maximum is odd, we cannot divide it anymore
        if (maxVal % 2 != 0) {
            break;
        }

        // Divide the max element by 2 and push back
        maxVal /= 2;
        if (maxVal < minVal) {
            minVal = maxVal; // Update minVal if the halved value is smaller
        }
        maxHeapInsert(maxHeap, maxVal);
    }

    free(maxHeap->arr);
    free(maxHeap);
    return minDeviation;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);

    int result = minimumDeviation(nums, n);
    printf("Minimum Deviation: %d\n", result);

    return 0;
}