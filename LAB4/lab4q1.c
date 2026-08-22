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

// Utility function to convert enum to string
const char* getColorName(Color color) {
    switch (color) {
        case RED:    return "RED";
        case BLUE:   return "BLUE";
        case YELLOW: return "YELLOW";
        default:     return "UNKNOWN";
    }
}

/**
 * Stable O(n) Color Sort Algorithm
 * Time Complexity: O(n)
 * Auxiliary Space Complexity: O(n)
 */
void sortByColor(Item arr[], int n) {
    if (n <= 1) return;

    int count[3] = {0};
    Item* output = (Item*)malloc(n * sizeof(Item));
    if (!output) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // 1. Calculate frequency of each color: O(n)
    for (int i = 0; i < n; i++) {
        count[arr[i].color]++;
    }

    // 2. Calculate starting index bounds for RED, BLUE, YELLOW
    int pos[3];
    pos[RED] = 0;
    pos[BLUE] = count[RED];
    pos[YELLOW] = count[RED] + count[BLUE];

    // 3. Stable distribution: preserves numeric relative order: O(n)
    for (int i = 0; i < n; i++) {
        output[pos[arr[i].color]++] = arr[i];
    }

    // 4. Copy sorted output back to input array: O(n)
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void printItems(const Item arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %s) ", arr[i].number, getColorName(arr[i].color));
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    Item* arr = (Item*)malloc(n * sizeof(Item));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter %d item pairs (number pre-sorted, color choice):\n", n);
    printf("Color Choices: 0 -> RED, 1 -> BLUE, 2 -> YELLOW\n\n");

    for (int i = 0; i < n; i++) {
        int colorChoice;
        printf("Item %d - Enter Number: ", i + 1);
        scanf("%d", &arr[i].number);

        do {
            printf("Item %d - Enter Color (0=RED, 1=BLUE, 2=YELLOW): ", i + 1);
            scanf("%d", &colorChoice);
            if (colorChoice < 0 || colorChoice > 2) {
                printf("Invalid color choice! Please choose 0, 1, or 2.\n");
            }
        } while (colorChoice < 0 || colorChoice > 2);

        arr[i].color = (Color)colorChoice;
    }

    printf("\n=== Initial Input Array ===\n");
    printItems(arr, n);

    sortByColor(arr, n);

    printf("\n=== Sorted Array (RED -> BLUE -> YELLOW) ===\n");
    printItems(arr, n);

    free(arr);
    return 0;
}
