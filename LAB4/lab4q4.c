#include <stdio.h>
#include <stdlib.h>

// Event Structure: type +1 for ENTRY, -1 for EXIT
typedef struct {
    int time;
    int type; 
} Event;

// Explicit comparator to avoid integer subtraction overflow bugs
int compareEvents(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;
    
    if (e1->time < e2->time) return -1;
    if (e1->time > e2->time) return 1;
    return 0;
}

void findPeakTime(const int a[], const int b[], int n) {
    if (n <= 0) {
        printf("Invalid number of persons.\n");
        return;
    }

    // Allocate 2n events for n entry and n exit points
    Event *events = (Event *)malloc(2 * n * sizeof(Event));
    if (!events) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // Populating entry and exit events
    for (int i = 0; i < n; i++) {
        events[2 * i].time = a[i];
        events[2 * i].type = 1;   // Person enters

        events[2 * i + 1].time = b[i];
        events[2 * i + 1].type = -1;  // Person exits
    }

    // Step 1: Sort events by timestamp -> O(n log n)
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int current_count = 0;
    int max_count = 0;
    int peak_time = -1;

    // Step 2: Linear sweep -> O(n)
    for (int i = 0; i < 2 * n; i++) {
        current_count += events[i].type;

        if (current_count > max_count) {
            max_count = current_count;
            peak_time = events[i].time;
        }
    }

    printf("\n--- Result ---\n");
    printf("Time of maximum attendance: %d\n", peak_time);
    printf("Maximum simultaneous people present: %d\n", max_count);

    free(events);
}

int main() {
    int n;

    printf("Enter number of persons (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    if (!a || !b) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(a);
        free(b);
        return 1;
    }

    printf("Enter entry time (a_i) and exit time (b_i) for each person:\n");
    for (int i = 0; i < n; i++) {
        printf("Person %d (a_i b_i): ", i + 1);
        if (scanf("%d %d", &a[i], &b[i]) != 2 || b[i] <= a[i]) {
            printf("Invalid entry/exit times. Ensure b_i > a_i.\n");
            free(a);
            free(b);
            return 1;
        }
    }

    findPeakTime(a, b, n);

    free(a);
    free(b);
    return 0;
}