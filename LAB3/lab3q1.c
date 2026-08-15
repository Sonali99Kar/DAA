#include <stdio.h>
#include <stdlib.h>

// Global counters to track total comparisons
int binary_comparisons = 0;
int ternary_comparisons = 0;

// Binary Search Implementation
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        binary_comparisons++;
        if (arr[mid] == key)
            return mid;

        binary_comparisons++;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Ternary Search Implementation
int ternarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ternary_comparisons++;
        if (arr[mid1] == key)
            return mid1;

        ternary_comparisons++;
        if (arr[mid2] == key)
            return mid2;

        ternary_comparisons++;
        if (key < arr[mid1]) {
            high = mid1 - 1;
        } else {
            ternary_comparisons++;
            if (key > arr[mid2]) {
                low = mid2 + 1;
            } else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
    return -1;
}

int main() {
    int n = 10000;
    int *arr = (int *)malloc(n * sizeof(int));

    // Initialize sorted array
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2; // [0, 2, 4, 6, ..., 19998]
    }

    int target = 18888; // Target element to search

    int bin_idx = binarySearch(arr, 0, n - 1, target);
    int tern_idx = ternarySearch(arr, 0, n - 1, target);

    printf("=========================================\n");
    printf("Array Size (n): %d\n", n);
    printf("Target Element: %d\n", target);
    printf("=========================================\n");
    printf("Binary Search  -> Index: %d | Comparisons: %d\n", bin_idx, binary_comparisons);
    printf("Ternary Search -> Index: %d | Comparisons: %d\n", tern_idx, ternary_comparisons);
    printf("=========================================\n");

    if (binary_comparisons < ternary_comparisons) {
        printf("Validation Successful: Binary Search required FEWER comparisons than Ternary Search.\n");
    }

    free(arr);
    return 0;
}
