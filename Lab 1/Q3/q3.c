#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Version 1: Stops early if the array becomes sorted
long long bubble_sort_v1(int arr[], int n) {
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++) {
        int swapped = 0; // Tracks if any elements swapped in this pass

        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                // Swap adjacent elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1; // Mark that a swap occurred
            }
        }

        // If no swaps happened, array is already sorted—stop early!
        if (swapped == 0) {
            break;
        }
    }

    return comparisons;
}

// Version 2: Always runs all (n - 1) passes regardless of order
long long bubble_sort_v2(int arr[], int n) {
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main() {
    srand((unsigned int)time(NULL));

    int sizes[] = {100, 500, 1000, 2000};
    int num_sizes = 4;

    printf("Array Size\tVersion 1 (Optimized)\tVersion 2 (Standard)\n");
    printf("-----------------------------------------------------------\n");

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];

        // Create two identical arrays filled with random numbers
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int val = rand() % 10000;
            arr1[i] = val;
            arr2[i] = val;
        }

        long long comp1 = bubble_sort_v1(arr1, n);
        long long comp2 = bubble_sort_v2(arr2, n);

        printf("%d\t\t%lld\t\t\t%lld\n", n, comp1, comp2);

        free(arr1);
        free(arr2);
    }

    return 0;
}
