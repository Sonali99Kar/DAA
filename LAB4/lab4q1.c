#include <stdio.h>
#include <stdlib.h>

// Input Representation
typedef enum {
    RED = 0,
    BLUE = 1,
    YELLOW = 2
} Color;

typedef struct {
    int number;
    Color color;
} Item;

// Helper function to map enum to readable names
const char* getColorName(Color color) {
    switch (color) {
        case RED:    return "RED";
        case BLUE:   return "BLUE";
        case YELLOW: return "YELLOW";
        default:     return "UNKNOWN";
    }
}

/**
 * Stable O(n) Color Sort implementation using Counting distribution.
 * Time Complexity: O(n) - Single forward pass for counts, offset placement, and copy-back.
 * Space Complexity: O(n) - Auxiliary array used to preserve original order.
 */
void sortByColor(Item arr[], int n) {
    if (n <= 1) return;

    int count[3] = {0};
    Item* output = (Item*)malloc(n * sizeof(Item));
    if (!output) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // 1. Calculate frequencies for each color: O(n)
    for (int i = 0; i < n; i++) {
        count[arr[i].color]++;
    }

    // 2. Compute starting indices (prefix offsets) for RED, BLUE, and YELLOW
    int pos[3];
    pos[RED] = 0;
    pos[BLUE] = count[RED];
    pos[YELLOW] = count[RED] + count[BLUE];

    // 3. Stable distribution: place items in order to maintain numeric sequence: O(n)
    for (int i = 0; i < n; i++) {
        output[pos[arr[i].color]++] = arr[i];
    }

    // 4. Copy sorted items back to original array: O(n)
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void printItems(const Item arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %-6s) ", arr[i].number, getColorName(arr[i].color));
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    // Test dataset pre-sorted by number
    Item arr[] = {
        {10, BLUE},   {15, RED},    {20, YELLOW}, 
        {25, RED},    {30, BLUE},   {35, YELLOW}, 
        {40, RED},    {42, BLUE},   {50, RED}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Input Array (Pre-sorted by Number) ===\n");
    printItems(arr, n);

    sortByColor(arr, n);

    printf("=== Output Array (Sorted by Color: RED -> BLUE -> YELLOW) ===\n");
    printItems(arr, n);

    return 0;
}
