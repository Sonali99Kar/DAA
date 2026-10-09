#include <stdio.h>
#include <stdlib.h>

// Structure to represent a meeting interval
typedef struct {
    int start;
    int end;
} Interval;

// Comparison function for sorting start times
int compareStart(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Comparison function for sorting end times
int compareEnd(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to find the minimum number of conference rooms required
int minMeetingRooms(Interval intervals[], int n) {
    if (n <= 0) return 0;

    int* starts = (int*)malloc(n * sizeof(int));
    int* ends = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        starts[i] = intervals[i].start;
        ends[i] = intervals[i].end;
    }

    // Sort start and end times independently
    qsort(starts, n, sizeof(int), compareStart);
    qsort(ends, n, sizeof(int), compareEnd);

    int rooms = 0;
    int maxRooms = 0;
    int sPtr = 0, ePtr = 0;

    // Sweep-line algorithm over start and end events
    while (sPtr < n) {
        if (starts[sPtr] < ends[ePtr]) {
            // A new meeting starts before the previous one ends -> Need a room
            rooms++;
            sPtr++;
        } else {
            // A meeting has ended -> Free up a room
            rooms--;
            ePtr++;
        }
        if (rooms > maxRooms) {
            maxRooms = rooms;
        }
    }

    free(starts);
    free(ends);
    return maxRooms;
}

int main() {
    // Example intervals: {[0, 30], [5, 10], [15, 20]}
    Interval intervals[] = {
        {0, 30},
        {5, 10},
        {15, 20}
    };
    int n = sizeof(intervals) / sizeof(intervals[0]);

    int result = minMeetingRooms(intervals, n);
    printf("Minimum number of meeting rooms required: %d\n", result);

    return 0;
}