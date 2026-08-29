#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition Scheme
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Standard Quicksort Algorithm
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quicksort(arr, low, pivotIndex - 1);  // Left subarray
        quicksort(arr, pivotIndex + 1, high); // Right subarray
    }
}

// Helper to generate N random numbers and save to input.txt
void generateRandomFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", rand() % 10000); // Random numbers between 0 and 9999
    }

    fclose(fp);
    printf("Generated %d random numbers in '%s'.\n", n, filename);
}

int main() {
    int n = 1000; // Number of elements
    const char *inputFile = "input.txt";
    const char *outputFile = "sorted.txt";

    // 1. Generate random numbers to input file
    generateRandomFile(inputFile, n);

    // 2. Read elements from input file into an array
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

    // 3. Sort array using Quicksort
    quicksort(arr, 0, n - 1);

    // 4. Save sorted array to output file
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
    printf("Successfully sorted data and saved to '%s'.\n", outputFile);

    free(arr);
    return 0;
}
