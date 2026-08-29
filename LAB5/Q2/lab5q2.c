#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition Scheme
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
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

// Quickselect function (k is 1-based index)
int quickselect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);

        // Target index in 0-based array is (k - 1)
        if (pivotIndex == k - 1) {
            return arr[pivotIndex];
        }
        else if (pivotIndex > k - 1) {
            return quickselect(arr, low, pivotIndex - 1, k);
        }
        else {
            return quickselect(arr, pivotIndex + 1, high, k);
        }
    }
    return -1;
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3; // Find the 3rd smallest element

    int result = quickselect(arr, 0, n - 1, k);
    printf("The %d-th smallest element is: %d\n", k, result);

    return 0;
}
