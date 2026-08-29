#include <stdio.h>

// Helper function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partitioning Scheme
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quickselect function to find the k-th smallest element (0-indexed)
int quickselect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);

        // If pivot is at the k-th position, we found our answer
        if (pivotIndex == k) {
            return arr[pivotIndex];
        }
        // If k is smaller, search the left sub-array
        else if (pivotIndex > k) {
            return quickselect(arr, low, pivotIndex - 1, k);
        }
        // If k is larger, search the right sub-array
        else {
            return quickselect(arr, pivotIndex + 1, high, k);
        }
    }
    return -1;
}

// Function to find median
double findMedian(int arr[], int n) {
    if (n % 2 != 0) {
        // Odd length: middle element at index n / 2
        return (double)quickselect(arr, 0, n - 1, n / 2);
    } else {
        // Even length: average of elements at (n/2 - 1) and (n/2)
        int mid1 = quickselect(arr, 0, n - 1, n / 2 - 1);
        int mid2 = quickselect(arr, 0, n - 1, n / 2);
        return (mid1 + mid2) / 2.0;
    }
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Median: %.1f\n", findMedian(arr, n));
    return 0;
}
