#include <stdio.h>

void selectionSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Find the smallest element in A[i...n-1]
        for (int j = i + 1; j < n; j++) {
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

int main() {
    int A[] = {64, 25, 12, 22, 11};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Original Array: ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    selectionSort(A, n);

    printf("Sorted Array:   ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    return 0;
}
