#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with node i (0-indexed)
// n is the size of the heap
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child index
    int right = 2 * i + 2; // Right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main Heap Sort function
void heapSort(int arr[], int n) {
    // Step 1: Build max heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Step 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to generate N random integers and write to file
void generateRandomFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", rand() % 10000); // Random integers [0, 9999]
    }

    fclose(fp);
    printf("Generated %d random numbers in '%s'.\n", n, filename);
}

int main() {
    int n = 1000; // Total elements
    const char *inputFile = "input.txt";
    const char *outputFile = "sorted.txt";

    // 1. Generate N random numbers to file
    generateRandomFile(inputFile, n);

    // 2. Read elements from input file
    FILE *fpInput = fopen(inputFile, "r");
    if (!fpInput) {
        perror("Error opening input file");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fpInput, "%d", &arr[i]);
    }
    fclose(fpInput);

    // 3. Perform Heap Sort
    heapSort(arr, n);

    // 4. Save sorted output to destination file
    FILE *fpOutput = fopen(outputFile, "w");
    if (!fpOutput) {
        perror("Error opening output file");
        free(arr);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fpOutput, "%d\n", arr[i]);
    }
    fclose(fpOutput);
    printf("Successfully sorted data using Heap Sort and saved to '%s'.\n", outputFile);

    free(arr);
    return 0;
}
