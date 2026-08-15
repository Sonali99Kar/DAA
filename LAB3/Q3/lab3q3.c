#include <stdio.h>
#include <stdlib.h>

// Structure to return both minimum and maximum elements
typedef struct {
    int min;
    int max;
} MinMax;

// Global variable to keep track of the total element comparisons
int comparison_count = 0;

/**
 * Divide and Conquer function to find minimum and maximum in arr[low...high].
 */
MinMax findMinMax(int arr[], int low, int high) {
    MinMax result, leftResult, rightResult;

    // Base Case 1: Only 1 element
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // Base Case 2: Exactly 2 elements
    if (high == low + 1) {
        comparison_count++; // 1 comparison made
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    // Divide Step: Find midpoint
    int mid = low + (high - low) / 2;

    // Conquer Step: Solve recursively for both halves
    leftResult = findMinMax(arr, low, mid);
    rightResult = findMinMax(arr, mid + 1, high);

    // Combine Step: Compare minimums (1 comparison)
    comparison_count++;
    if (leftResult.min < rightResult.min) {
        result.min = leftResult.min;
    } else {
        result.min = rightResult.min;
    }

    // Combine Step: Compare maximums (1 comparison)
    comparison_count++;
    if (leftResult.max > rightResult.max) {
        result.max = leftResult.max;
    } else {
        result.max = rightResult.max;
    }

    return result;
}

int main() {
    int arr[] = {34, 12, 9, 87, 65, 23, 1, 99, 45, 18, 72, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    comparison_count = 0;
    MinMax res = findMinMax(arr, 0, n - 1);

    int theoretical_bound = (3 * n) / 2;

    printf("=========================================\n");
    printf("Array Size (n): %d\n", n);
    printf("Array Elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n=========================================\n");
    printf("Minimum Element: %d\n", res.min);
    printf("Maximum Element: %d\n", res.max);
    printf("-----------------------------------------\n");
    printf("Actual Comparisons Made : %d\n", comparison_count);
    printf("Theoretical Bound (3n/2): %d\n", theoretical_bound);
    printf("=========================================\n");

    if (comparison_count <= theoretical_bound) {
        printf("Validation Successful: Comparisons (%d) <= 3n/2 (%d)\n", 
               comparison_count, theoretical_bound);
    }

    return 0;
}
