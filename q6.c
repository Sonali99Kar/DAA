#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Helper comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Method to check for duplicate elements in O(n log n) time
bool check_element_uniqueness(int arr[], int n) {
    // Step 1: Sort the array in ascending order
    qsort(arr, n, sizeof(int), compare);

    // Step 2: Check adjacent elements for duplicates
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            return true; // Duplicate found!
        }
    }

    return false; // All elements are unique
}

int main() {
    srand((unsigned int)time(NULL));

    int n = 10000;
    int *arr = (int *)malloc(n * sizeof(int));

    // Generate random numbers between 0 and 50000
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 50000;
    }

    if (check_element_uniqueness(arr, n)) {
        printf("Result: Duplicate elements were FOUND in the array.\n");
    } else {
        printf("Result: All elements in the array are UNIQUE.\n");
    }

    free(arr);
    return 0;
}