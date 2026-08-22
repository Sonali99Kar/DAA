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

// Binary Search in range [low, high]: O(log n)
int binarySearch(const int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

/**
 * Recursive Helper for k-Sum with O(n^(k-1) log n) complexity.
 * @param arr Sorted input array
 * @param n Size of input array
 * @param start Index to start selecting from
 * @param k Remaining number of elements to pick
 * @param target Remaining target sum
 * @param indices Array storing selected indices for output
 */
bool kSumHelper(const int arr[], int n, int start, int k, int target, int indices[]) {
    // Base Case: When k = 2, fix 1 element with loop and binary search the last -> O(n log n)
    if (k == 2) {
        for (int i = start; i < n - 1; i++) {
            int needed = target - arr[i];
            int foundIdx = binarySearch(arr, i + 1, n - 1, needed);
            if (foundIdx != -1) {
                indices[0] = i;
                indices[1] = foundIdx;
                return true;
            }
        }
        return false;
    }

    // Fix current element and recursively solve for (k - 1)
    for (int i = start; i <= n - k; i++) {
        if (kSumHelper(arr, n, i + 1, k - 1, target - arr[i], indices + 1)) {
            indices[0] = i;
            return true;
        }
    }

    return false;
}

// Wrapper function: O(n log n) initial sort + O(n^(k-1) log n) search
bool hasKSum(int S[], int n, int k, int T, int result[]) {
    if (k > n || k <= 0) return false;

    // 1. Sort the set: O(n log n)
    qsort(S, n, sizeof(int), compare);

    int *indices = (int *)malloc(k * sizeof(int));
    bool found = kSumHelper(S, n, 0, k, T, indices);

    if (found && result) {
        for (int i = 0; i < k; i++) {
            result[i] = S[indices[i]];
        }
    }

    free(indices);
    return found;
}

int main() {
    int n, k, T;

    printf("Enter number of elements in set S (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *S = (int *)malloc(n * sizeof(int));
    if (!S) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers for set S:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    printf("Enter k (number of integers to sum): ");
    scanf("%d", &k);

    printf("Enter target sum T: ");
    scanf("%d", &T);

    int *result = (int *)malloc(k * sizeof(int));

    if (hasKSum(S, n, k, T, result)) {
        printf("\nResult: Found %d elements that sum to %d:\n", k, T);
        for (int i = 0; i < k; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("\nResult: No %d elements in S sum up to %d.\n", k, T);
    }

    free(S);
    free(result);
    return 0;
}
