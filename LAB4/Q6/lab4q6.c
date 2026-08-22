#include <stdio.h>
#include <stdlib.h>

// Event Types
#define START 1
#define END   -1

// Data structure for sweep-line events
typedef struct {
    int point;
    int type; // +1 for START, -1 for END
} Event;

// Data structure for input intervals
typedef struct {
    int left;
    int right;
} Interval;

// Custom comparator for qsort
int compareEvents(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    // Primary sort: ascending order of coordinate point
    if (e1->point != e2->point) {
        return (e1->point - e2->point);
    }
    
    // Secondary tie-breaker: START (+1) comes before END (-1)
    // to include endpoints inclusively
    return (e2->type - e1->type);
}

/**
 * Finds a point p that intersects the largest number of intervals.
 * Time Complexity: O(n log n)
 * Auxiliary Space: O(n)
 */
void findMaxOverlapPoint(const Interval intervals[], int n) {
    if (n <= 0) {
        printf("Invalid number of intervals.\n");
        return;
    }

    // Allocate 2n events for n intervals
    Event *events = (Event *)malloc(2 * n * sizeof(Event));
    if (!events) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // Create start and end events for each interval
    for (int i = 0; i < n; i++) {
        events[2 * i].point = intervals[i].left;
        events[2 * i].type = START;

        events[2 * i + 1].point = intervals[i].right;
        events[2 * i + 1].type = END;
    }

    // Step 1: Sort events -> O(n log n)
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = events[0].point;

    // Step 2: Linear sweep through sorted events -> O(n)
    for (int i = 0; i < 2 * n; i++) {
        current_overlap += events[i].type;

        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = events[i].point;
        }
    }

    printf("\n=== Analysis Results ===\n");
    printf("Point p in maximum intervals: %d\n", best_point);
    printf("Maximum number of overlapping intervals: %d\n", max_overlap);

    free(events);
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

    printf("Enter %d intervals as (l_i r_i) pairs:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Interval %d (l_i r_i): ", i + 1);
        if (scanf("%d %d", &intervals[i].left, &intervals[i].right) != 2 || intervals[i].left > intervals[i].right) {
            printf("Invalid interval range. Ensure left <= right.\n");
            free(intervals);
            return 1;
        }
    }

    findMaxOverlapPoint(intervals, n);

    free(intervals);
    return 0;
}
