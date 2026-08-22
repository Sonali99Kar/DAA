#include <stdio.h>
#include <stdlib.h>

// Input and Output Representation
typedef struct {
    int start; // x_i
    int end;   // y_i
} Interval;

// Utility function to get max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Comparator function to sort intervals by start value x_i
int compareIntervals(const void *a, const void *b) {
    const Interval *i1 = (const Interval *)a;
    const Interval *i2 = (const Interval *)b;

    if (i1->start < i2->start) return -1;
    if (i1->start > i2->start) return 1;
    return 0;
}

/**
 * Merges overlapping intervals in O(n log n) time.
 * @param intervals Array of input intervals
 * @param n Total number of intervals
 * @param mergedCount Pointer to return the size of merged array
 * @return Array of merged intervals
 */
Interval* mergeIntervals(Interval intervals[], int n, int *mergedCount) {
    if (n <= 0) {
        *mergedCount = 0;
        return NULL;
    }

    // Step 1: Sort intervals by start value -> O(n log n)
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    // Dynamic memory for merged results
    Interval *merged = (Interval *)malloc(n * sizeof(Interval));
    if (!merged) {
        fprintf(stderr, "Memory allocation failed.\n");
        *mergedCount = 0;
        return NULL;
    }

    int count = 0;
    merged[count++] = intervals[0];

    // Step 2: Linear pass to merge overlapping intervals -> O(n)
    for (int i = 1; i < n; i++) {
        Interval *last = &merged[count - 1];

        if (intervals[i].start <= last->end) {
            // Overlap detected: extend end coordinate
            last->end = max(last->end, intervals[i].end);
        } else {
            // No overlap: add as new interval
            merged[count++] = intervals[i];
        }
    }

    *mergedCount = count;
    return merged;
}

void printIntervals(const Interval arr[], int n) {
    printf("{");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)", arr[i].start, arr[i].end);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");
}

int main() {
    int n;

    printf("Enter number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    Interval *intervals = (Interval *)malloc(n * sizeof(Interval));
    if (!intervals) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d interval pairs (x_i y_i):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        if (scanf("%d %d", &intervals[i].start, &intervals[i].end) != 2 || intervals[i].start > intervals[i].end) {
            printf("Invalid interval range. Ensure start <= end.\n");
            free(intervals);
            return 1;
        }
    }

    printf("\nOriginal Intervals: ");
    printIntervals(intervals, n);

    int mergedCount = 0;
    Interval *merged = mergeIntervals(intervals, n, &mergedCount);

    printf("Merged Intervals:   ");
    printIntervals(merged, mergedCount);

    free(intervals);
    free(merged);
    return 0;
}