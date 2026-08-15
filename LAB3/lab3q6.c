#include <stdio.h>

// Function to perform Selection Sort and track comparisons
void selectionSort(int A[], int n, int *comparisons) {
    *comparisons = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Inner loop: Find the minimum in unsorted portion A[i...n-1]
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (A[j] < A[minIndex]) {
                minIndex = j;
            }
        }

        // Swap A[i] and A[minIndex]
        if (minIndex != i) {
            int temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
        }
    }
}

// Helper function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 6;
    int theoretical_comparisons = (n * (n - 1)) / 2; // n(n-1)/2 = 15

    // Test Case 1: Worst Case (Reverse Sorted)
    int worst_case[] = {60, 50, 40, 30, 20, 10};
    int worst_comparisons = 0;

    printf("================ WORST CASE ================\n");
    printf("Original: ");
    printArray(worst_case, n);

    selectionSort(worst_case, n, &worst_comparisons);

    printf("Sorted:   ");
    printArray(worst_case, n);
    printf("Comparisons: %d (Expected: %d)\n\n", worst_comparisons, theoretical_comparisons);

    // Test Case 2: Best Case (Already Sorted)
    int best_case[] = {10, 20, 30, 40, 50, 60};
    int best_comparisons = 0;

    printf("================ BEST CASE ================\n");
    printf("Original: ");
    printArray(best_case, n);

    selectionSort(best_case, n, &best_comparisons);

    printf("Sorted:   ");
    printArray(best_case, n);
    printf("Comparisons: %d (Expected: %d)\n", best_comparisons, theoretical_comparisons);
    printf("===========================================\n");

    return 0;
}