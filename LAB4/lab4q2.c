#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    int val1 = *(const int *)a;
    int val2 = *(const int *)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

// Binary Search implementation: O(log n)
bool binarySearch(const int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

// Checks if there exist a in S1 and b in S2 such that a + b = x: O(n log n)
bool hasTargetSumPair(int S1[], int S2[], int n, int x, int *found_a, int *found_b) {
    // Step 1: Sort S1 -> O(n log n)
    qsort(S1, n, sizeof(int), compare);

    // Step 2: For each element b in S2, search x - b in sorted S1 -> O(n log n)
    for (int i = 0; i < n; i++) {
        int target = x - S2[i];
        if (binarySearch(S1, n, target)) {
            if (found_a) *found_a = target;
            if (found_b) *found_b = S2[i];
            return true;
        }
    }
    return false;
}

int main() {
    int n, x;

    printf("Enter set size (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid set size.\n");
        return 1;
    }

    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));

    if (!S1 || !S2) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(S1);
        free(S2);
        return 1;
    }

    printf("Enter %d elements for Set S1:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter %d elements for Set S2:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    printf("Enter target sum (x): ");
    scanf("%d", &x);

    int a = 0, b = 0;
    if (hasTargetSumPair(S1, S2, n, x, &a, &b)) {
        printf("\nResult: Found pair! %d (from S1) + %d (from S2) = %d\n", a, b, x);
    } else {
        printf("\nResult: No pair found in S1 and S2 that sums up to %d\n", x);
    }

    free(S1);
    free(S2);
    return 0;
}