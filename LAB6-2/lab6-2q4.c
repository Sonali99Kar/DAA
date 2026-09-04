#include <stdio.h>

// Global variable to track the cost of reversals
long long total_cost = 0;

// Reverses the subarray arr[i...j] and adds the length to the total cost
void reverse(int arr[], int i, int j) {
    if (i >= j) return;
    total_cost += (j - i + 1); // Cost = |j - i| + 1
    
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

// Rotates the block to swap arr[start...mid-1] and arr[mid...end]
// using 3 sequential reversals
void rotate(int arr[], int start, int mid, int end) {
    if (start >= mid || mid > end) return;
    reverse(arr, start, mid - 1);
    reverse(arr, mid, end);
    reverse(arr, start, end);
}

// Standard Binary Search to find the upper bound
int binarySearch(int arr[], int key, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

// Merges two sorted subarrays arr[start...mid-1] and arr[mid...end] in-place
void inPlaceMerge(int arr[], int start, int mid, int end) {
    if (start >= mid || mid > end) return;
    
    int lenA = mid - start;
    int lenB = end - mid + 1;
    if (lenA == 0 || lenB == 0) return;

    int midA, midB;
    // Always pick the median of the larger subarray to ensure logarithmic depth
    if (lenA >= lenB) {
        midA = start + lenA / 2;
        midB = binarySearch(arr, arr[midA], mid, end);
    } else {
        midB = mid + lenB / 2;
        midA = binarySearch(arr, arr[midB], start, mid - 1);
    }

    // Rotate A2 and B1. A2 is arr[midA...mid-1], B1 is arr[mid...midB-1]
    rotate(arr, midA, mid, midB - 1);

    // Calculate the new partition point after rotation
    int new_mid = midA + (midB - mid);

    // Recursively merge the left and right halves
    inPlaceMerge(arr, start, midA, new_mid - 1);
    inPlaceMerge(arr, new_mid + 1, midB, end); // +1 to skip the pivot which is correctly placed
}

// Divide and Conquer Merge Sort
void mergeSort(int arr[], int start, int end) {
    if (start >= end) return;
    
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    
    // mid+1 is the start of the right subarray
    inPlaceMerge(arr, start, mid + 1, end); 
}

// Utility to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 1, 15, 3, 9, 8, 2, 4, 14, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original permutation: \n");
    printArray(arr, n);

    total_cost = 0; // Reset cost
    mergeSort(arr, 0, n - 1);

    printf("\nSorted array using only reversals: \n");
    printArray(arr, n);
    
    printf("\nTotal Cost of Reversals: %lld\n", total_cost);
    printf("Theoretical bound O(N log^2 N) roughly expects a proportional cost.\n");

    return 0;
}