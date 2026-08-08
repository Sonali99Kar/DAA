#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper to copy elements
void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// ==========================================
// 1. STANDARD MERGE SORT (2-WAY SPLIT)
// ==========================================
void merge_2way(int arr[], int l, int m, int r) {
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

    free(L);
    free(R);
}

void merge_sort_2way(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_2way(arr, l, m);
        merge_sort_2way(arr, m + 1, r);
        merge_2way(arr, l, m, r);
    }
}

// ==========================================
// 2. MODIFIED MERGE SORT (3-WAY SPLIT)
// ==========================================
void merge_3way(int arr[], int l, int mid1, int mid2, int r) {
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

    // 3-way merge loop
    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j] && L[i] <= R[k]) arr[idx++] = L[i++];
        else if (M[j] <= L[i] && M[j] <= R[k]) arr[idx++] = M[j++];
        else arr[idx++] = R[k++];
    }

    // Merge remaining elements of two sub-arrays
    while (i < n1 && j < n2) arr[idx++] = (L[i] <= M[j]) ? L[i++] : M[j++];
    while (j < n2 && k < n3) arr[idx++] = (M[j] <= R[k]) ? M[j++] : R[k++];
    while (i < n1 && k < n3) arr[idx++] = (L[i] <= R[k]) ? L[i++] : R[k++];

    // Merge remaining single sub-array elements
    while (i < n1) arr[idx++] = L[i++];
    while (j < n2) arr[idx++] = M[j++];
    while (k < n3) arr[idx++] = R[k++];

    free(L);
    free(M);
    free(R);
}

void merge_sort_3way(int arr[], int l, int r) {
    if (l < r) {
        if (r - l < 2) {
            // For less than 3 elements, fallback to simple comparison
            if (arr[l] > arr[r]) {
                int temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
            }
            return;
        }

        int mid1 = l + (r - l) / 3;
        int mid2 = l + 2 * (r - l) / 3;

        merge_sort_3way(arr, l, mid1);
        merge_sort_3way(arr, mid1 + 1, mid2);
        merge_sort_3way(arr, mid2 + 1, r);

        merge_3way(arr, l, mid1, mid2, r);
    }
}

int main() {
    FILE *fp = fopen("q2_merge_data.txt", "w");
    if (!fp) {
        printf("Error creating data file!\n");
        return 1;
    }

    srand(42);
    printf("Benchmarking Standard vs 3-Way Merge Sort...\n");

    for (int n = 10000; n <= 100000; n += 10000) {
        int *orig = (int *)malloc(n * sizeof(int));
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) orig[i] = rand() % 100000;

        // Measure Standard 2-Way Merge Sort
        copy_array(orig, arr1, n);
        clock_t start = clock();
        for (int t = 0; t < 5; t++) {
            copy_array(orig, arr1, n);
            merge_sort_2way(arr1, 0, n - 1);
        }
        double t_2way = ((double)(clock() - start)) / CLOCKS_PER_SEC / 5.0;

        // Measure Modified 3-Way Merge Sort
        copy_array(orig, arr2, n);
        start = clock();
        for (int t = 0; t < 5; t++) {
            copy_array(orig, arr2, n);
            merge_sort_3way(arr2, 0, n - 1);
        }
        double t_3way = ((double)(clock() - start)) / CLOCKS_PER_SEC / 5.0;

        fprintf(fp, "%d %f %f\n", n, t_2way, t_3way);

        free(orig);
        free(arr1);
        free(arr2);
    }

    fclose(fp);
    printf("Data generation complete. Plotting with Gnuplot...\n");

    // Launch Gnuplot to display the comparison graph
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot) {
        fprintf(gnuplot, "set title 'Standard (2-Way) vs Modified (3-Way) Merge Sort'\n");
        fprintf(gnuplot, "set xlabel 'Input Size (n)'\n");
        fprintf(gnuplot, "set ylabel 'Execution Time (seconds)'\n");
        fprintf(gnuplot, "set grid\n");

        // Color differentiate operations
        fprintf(gnuplot, "plot 'q2_merge_data.txt' using 1:2 with linespoints lc rgb '#FF0000' lw 2 title 'Standard Merge Sort (2-Way)', \\\n");
        fprintf(gnuplot, "     'q2_merge_data.txt' using 1:3 with linespoints lc rgb '#0000FF' lw 2 title 'Modified Merge Sort (3-Way)'\n");

        pclose(gnuplot);
    }

    return 0;
}
