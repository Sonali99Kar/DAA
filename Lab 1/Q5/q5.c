#include <stdio.h>

// Function to find the first index where 1 appears
int find_transition_index(int arr[], int n) {
    int low = 0;
    int high = n - 1;
    int first_one_index = -1; // Default if no 1s are found

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1) {
            first_one_index = mid; // Save current index as potential answer
            high = mid - 1;        // Keep searching left for an earlier 1
        } else {
            low = mid + 1;         // Search right half
        }
    }

    return first_one_index;
}

int main() {
    // Sample sorted array with a run of 0s followed by 1s
    int arr[] = {0, 0, 0, 0, 0, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int index = find_transition_index(arr, n);

    if (index == -1) {
        printf("The array contains only 0s.\n");
    } else if (index == 0) {
        printf("The array contains only 1s starting at index 0.\n");
    } else {
        printf("Transition Point Found:\n");
        printf("Last '0' is at index %d\n", index - 1);
        printf("First '1' is at index %d\n", index);
    }

    return 0;
}
