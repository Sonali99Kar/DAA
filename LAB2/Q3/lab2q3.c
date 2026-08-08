#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard 2-way merge helper function
void merge_two_arrays(int *arr1, int size1, int *arr2, int size2, int *result) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    while (i < size1) result[k++] = arr1[i++];
    while (j < size2) result[k++] = arr2[j++];
}

// =================================================================
// Method 1: Iterative Sequential Merging - O(k^2 * n)
// =================================================================
void merge_k_sequential(int **arrays, int k, int n, int *out) {
    int current_size = n;
    
    // Copy the first array to out
    for (int i = 0; i < n; i++) {
        out[i] = arrays[0][i];
    }
    
    // Iteratively merge the remaining (k - 1) arrays
    for (int i = 1; i < k; i++) {
        int *temp = (int *)malloc((current_size + n) * sizeof(int));
        merge_two_arrays(out, current_size, arrays[i], n, temp);
        
        current_size += n;
        for (int j = 0; j < current_size; j++) {
            out[j] = temp[j];
        }
        free(temp);
    }
}

// =================================================================
// Method 2: Pairwise Divide & Conquer Merging - O(k * n * log k)
// =================================================================
void merge_k_pairwise(int **arrays, int k, int n, int *out) {
    // Allocate space for working buffers
    int **current = (int **)malloc(k * sizeof(int *));
    int *sizes = (int *)malloc(k * sizeof(int));
    
    for (int i = 0; i < k; i++) {
        current[i] = (int *)malloc(n * sizeof(int));
        sizes[i] = n;
        for (int j = 0; j < n; j++) {
            current[i][j] = arrays[i][j];
        }
    }
    
    int active_k = k;
    while (active_k > 1) {
        int next_k = (active_k + 1) / 2;
        int **next_level = (int **)malloc(next_k * sizeof(int *));
        int *next_sizes = (int *)malloc(next_k * sizeof(int));
        
        int idx = 0;
        for (int i = 0; i < active_k; i += 2) {
            if (i + 1 < active_k) {
                int new_size = sizes[i] + sizes[i + 1];
                next_level[idx] = (int *)malloc(new_size * sizeof(int));
                next_sizes[idx] = new_size;
                merge_two_arrays(current[i], sizes[i], current[i + 1], sizes[i + 1], next_level[idx]);
                free(current[i]);
                free(current[i + 1]);
            } else {
                // Odd one out pass directly
                next_level[idx] = current[i];
                next_sizes[idx] = sizes[i];
            }
            idx++;
        }
        
        free(current);
        free(sizes);
        current = next_level;
        sizes = next_sizes;
        active_k = next_k;
    }
    
    // Copy final output
    for (int i = 0; i < k * n; i++) {
        out[i] = current[0][i];
    }
    
    free(current[0]);
    free(current);
    free(sizes);
}

// Helper function to create sorted arrays
int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    FILE *fp = fopen("q3_merge_data.txt", "w");
    if (!fp) {
        printf("Error creating file!\n");
        return 1;
    }

    srand(42);
    int n = 500; // Fixed size per array

    printf("Benchmarking Merging K Sorted Arrays (Fixed n = %d)...\n", n);
    printf("k\tMethod 1 (O(k^2 n))\tMethod 2 (O(kn log k))\n");

    for (int k = 10; k <= 200; k += 10) {
        // Allocate and populate k sorted arrays
        int **arrays = (int **)malloc(k * sizeof(int *));
        for (int i = 0; i < k; i++) {
            arrays[i] = (int *)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++) {
                arrays[i][j] = rand() % 100000;
            }
            qsort(arrays[i], n, sizeof(int), compare_ints);
        }

        int *out1 = (int *)malloc(k * n * sizeof(int));
        int *out2 = (int *)malloc(k * n * sizeof(int));

        // Time Method 1
        clock_t start = clock();
        merge_k_sequential(arrays, k, n, out1);
        double t_m1 = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Time Method 2
        start = clock();
        merge_k_pairwise(arrays, k, n, out2);
        double t_m2 = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        printf("%d\t%f s\t\t%f s\n", k, t_m1, t_m2);
        fprintf(fp, "%d %f %f\n", k, t_m1, t_m2);

        // Cleanup iteration
        for (int i = 0; i < k; i++) free(arrays[i]);
        free(arrays);
        free(out1);
        free(out2);
    }

    fclose(fp);
    printf("Benchmarking completed. Plotting results...\n");

    // Launch Gnuplot to graph results
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot) {
        fprintf(gnuplot, "set title 'Merging k Sorted Arrays: Method 1 vs Method 2'\n");
        fprintf(gnuplot, "set xlabel 'Number of Arrays (k)'\n");
        fprintf(gnuplot, "set ylabel 'Execution Time (seconds)'\n");
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot 'q3_merge_data.txt' using 1:2 with linespoints lc rgb '#FF0000' lw 2 title 'Method 1: Sequential O(k^2 n)', \\\n");
        fprintf(gnuplot, "     'q3_merge_data.txt' using 1:3 with linespoints lc rgb '#0000FF' lw 2 title 'Method 2: Pairwise O(kn log k)'\n");
        pclose(gnuplot);
    }

    return 0;
}
