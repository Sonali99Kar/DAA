#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Helper 2-Way Merge Subroutine ---
void merge2(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);
}

// Standard 2-Way Merge Sort
void mergeSort2(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort2(arr, l, m);
        mergeSort2(arr, m + 1, r);
        merge2(arr, l, m, r);
    }
}

// --- Helper 3-Way Merge Subroutine ---
void merge3(int arr[], int l, int mid1, int mid2, int r) {
    int n1 = mid1 - l + 1;
    int n2 = mid2 - mid1;
    int n3 = r - mid2;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *M = (int *)malloc(n2 * sizeof(int));
    int *R = (int *)malloc(n3 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) M[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < n3; i++) R[i] = arr[mid2 + 1 + i];

    int i = 0, j = 0, k = 0, idx = l;

    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j]) {
            if (L[i] <= R[k]) arr[idx++] = L[i++];
            else arr[idx++] = R[k++];
        } else {
            if (M[j] <= R[k]) arr[idx++] = M[j++];
            else arr[idx++] = R[k++];
        }
    }

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) arr[idx++] = L[i++];
        else arr[idx++] = M[j++];
    }

    while (j < n2 && k < n3) {
        if (M[j] <= R[k]) arr[idx++] = M[j++];
        else arr[idx++] = R[k++];
    }

    while (i < n1 && k < n3) {
        if (L[i] <= R[k]) arr[idx++] = L[i++];
        else arr[idx++] = R[k++];
    }

    while (i < n1) arr[idx++] = L[i++];
    while (j < n2) arr[idx++] = M[j++];
    while (k < n3) arr[idx++] = R[k++];

    free(L); free(M); free(R);
}

// Modified 3-Way Merge Sort
void mergeSort3(int arr[], int l, int r) {
    if (l < r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = l + 2 * (r - l) / 3;

        mergeSort3(arr, l, mid1);
        mergeSort3(arr, mid1 + 1, mid2);
        mergeSort3(arr, mid2 + 1, r);

        merge3(arr, l, mid1, mid2, r);
    }
}

int main() {
    FILE *fp = fopen("mergesort_data.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Measuring running times for 2-Way vs 3-Way Merge Sort...\n");

    // Increasing input size n from 10000 to 100000
    for (int n = 10000; n <= 100000; n += 10000) {
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int val = rand() % 100000;
            arr1[i] = val;
            arr2[i] = val;
        }

        // Measure 2-Way Merge Sort
        clock_t start = clock();
        mergeSort2(arr1, 0, n - 1);
        double t_2way = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Measure 3-Way Merge Sort
        start = clock();
        mergeSort3(arr2, 0, n - 1);
        double t_3way = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Write: n  2Way_Time  3Way_Time
        fprintf(fp, "%d %f %f\n", n, t_2way, t_3way);

        free(arr1);
        free(arr2);
    }

    fclose(fp);
    printf("Data written to 'mergesort_data.txt'. Launching Gnuplot...\n");

    // Send commands directly to Gnuplot
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot) {
        fprintf(gnuplot, "set title '2-Way Merge Sort vs 3-Way Merge Sort'\n");
        fprintf(gnuplot, "set xlabel 'Input Size (n)'\n");
        fprintf(gnuplot, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot 'mergesort_data.txt' using 1:2 with linespoints title 'Standard 2-Way Merge Sort', \\\n");
        fprintf(gnuplot, "     'mergesort_data.txt' using 1:3 with linespoints title '3-Way Modified Merge Sort'\n");
        pclose(gnuplot);
    }

    return 0;
}