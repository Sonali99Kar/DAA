#include <stdio.h>
#include <stdlib.h>

// Structure to represent a fuel station
typedef struct {
    int dist; // Distance from origin
    int fuel; // Refuel amount
} Station;

// Max-Heap structure for storing fuel amounts
typedef struct {
    int* arr;
    int size;
    int capacity;
} MaxHeap;

// Function to create a max-heap
MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

// Swap function
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up (Insert helper)
void maxHeapInsert(MaxHeap* heap, int fuel) {
    if (heap->size == heap->capacity) return;
    int i = heap->size++;
    heap->arr[i] = fuel;

    while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Heapify down (Extract max helper)
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
    if (heap->size == 1) return heap->arr[--heap->size];

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    maxHeapify(heap, 0);

    return root;
}

// Function to compare two stations by distance
int compareStations(const void* a, const void* b) {
    return ((Station*)a)->dist - ((Station*)b)->dist;
}

// Function to find minimum refueling stops
int minRefuelStops(int target, int startFuel, Station stations[], int n) {
    MaxHeap* maxHeap = createHeap(n + 1);
    int stops = 0;
    int current_fuel = startFuel;
    int i = 0;

    // Sort stations by distance
    qsort(stations, n, sizeof(Station), compareStations);

    int current_position = 0;
    while (current_position < target) {
        // Add all stations we can reach with our current fuel into the heap
        while (i < n && stations[i].dist <= current_fuel) {
            maxHeapInsert(maxHeap, stations[i].fuel);
            i++;
        }

        // If we run out of fuel and cannot reach any further station or target
        if (maxHeap->size == 0 && current_fuel < target) {
            free(maxHeap->arr);
            free(maxHeap);
            return -1;
        }

        // Greedily pick the station with the maximum fuel
        if (current_position < target && current_fuel < target) {
            current_fuel += extractMax(maxHeap);
            stops++;
        } else {
            break;
        }
    }

    free(maxHeap->arr);
    free(maxHeap);
    return stops;
}

int main() {
    int target = 100;
    int startFuel = 10;
    
    // Example stations: {distance, fuel}
    Station stations[] = {
        {10, 60},
        {20, 30},
        {30, 30},
        {60, 40}
    };
    int n = sizeof(stations) / sizeof(stations[0]);

    int result = minRefuelStops(target, startFuel, stations, n);
    if (result != -1)
        printf("Minimum refuelling stops required: %d\n", result);
    else
        printf("Target cannot be reached.\n");

    return 0;
}