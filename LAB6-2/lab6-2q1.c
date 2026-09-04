#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Helper function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// (i) Finding the maximum element
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

// (ii) Finding first and second largest
void findTopTwo(int arr[], int n) {
    int first = -2147483648, second = -2147483648;
    for (int i = 0; i < n; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }
    printf("First Largest: %d, Second Largest: %d\n", first, second);
}

// (iii) Finding the mean
double findMean(int arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

// (iv) Finding the median (Requires sorting)
double findMedian(int arr[], int n) {
    int temp[n];
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);
    
    if (n % 2 != 0) return temp[n / 2];
    return (temp[(n - 1) / 2] + temp[n / 2]) / 2.0;
}

// (v) Finding the standard deviation
double findStdDev(int arr[], int n) {
    double mean = findMean(arr, n);
    double varianceSum = 0;
    for (int i = 0; i < n; i++) {
        varianceSum += pow(arr[i] - mean, 2);
    }
    return sqrt(varianceSum / n);
}

// (vi) Finding the mode (Requires sorting)
int findMode(int arr[], int n) {
    int temp[n];
    for(int i=0; i<n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);

    int maxCount = 1, currentCount = 1, mode = temp[0];
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                mode = temp[i - 1];
            }
            currentCount = 1;
        }
    }
    // Check the last sequence
    if (currentCount > maxCount) mode = temp[n - 1]; 
    return mode;
}

// (vii) Removing all duplicates (Returns new size)
int removeDuplicates(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    int j = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[n - 1];
    return j; // New size of the array
}

// (viii) Reversing the elements
void reverseArray(int arr[], int n) {
    int start = 0, end = n - 1;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// (ix) Partitioning array around a pivot
void partitionArray(int arr[], int n, int pivot) {
    int left = 0, right = n - 1;
    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] >= pivot) right--;
        if (left <= right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}

// Utility to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 15, 10, 11, 16, 20, 12, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array: ");
    printArray(arr, n);

    printf("\n(i) Maximum Element: %d\n", findMax(arr, n));
    
    printf("(ii) ");
    findTopTwo(arr, n);
    
    printf("(iii) Mean: %.2f\n", findMean(arr, n));
    printf("(iv) Median: %.2f\n", findMedian(arr, n));
    printf("(v) Standard Deviation: %.2f\n", findStdDev(arr, n));
    printf("(vi) Mode: %d\n", findMode(arr, n));

    printf("\n(viii) Reversing the array:\n");
    reverseArray(arr, n);
    printArray(arr, n);
    
    // Reverse it back for partition
    reverseArray(arr, n); 

    int pivot = 13;
    printf("\n(ix) Partitioning array around pivot %d:\n", pivot);
    partitionArray(arr, n, pivot);
    printArray(arr, n);

    printf("\n(vii) Array after removing duplicates (also sorts it):\n");
    int newSize = removeDuplicates(arr, n);
    printArray(arr, newSize);

    return 0;
}
