#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find the maximum overlap between string A and string B (A's suffix with B's prefix)
// Returns the overlap length and copies the merged string into result
int getOverlap(char* a, char* b, char* result) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxOverlap = 0;

    // Try all possible overlap lengths
    for (int i = 1; i <= lenA && i <= lenB; i++) {
        // Check if suffix of a of length i matches prefix of b of length i
        if (strncmp(a + lenA - i, b, i) == 0) {
            maxOverlap = i;
        }
    }

    // Construct merged string: a + b excluding the overlapping prefix of b
    strcpy(result, a);
    strcat(result, b + maxOverlap);
    return maxOverlap;
}

// Greedy approximation function for Shortest Superstring
void shortestSuperstringGreedy(char* arr[], int n) {
    while (n > 1) {
        int maxOverlap = -1;
        int idx1 = 0, idx2 = 1;
        char merged[256];
        char bestMerged[256];

        // Find the pair with the maximum overlap
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                char temp[256];
                int overlap = getOverlap(arr[i], arr[j], temp);
                if (overlap > maxOverlap) {
                    maxOverlap = overlap;
                    idx1 = i;
                    idx2 = j;
                    strcpy(bestMerged, temp);
                }
            }
        }

        // Replace arr[idx1] with the best merged string and remove arr[idx2]
        arr[idx1] = strdup(bestMerged);
        for (int i = idx2; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        n--;
    }

    printf("Greedy Superstring Result: %s\n", arr[0]);
}

int main() {
    // Example input strings
    char* arr[] = {"catct", "ctaat", "tca"};
    int n = sizeof(arr) / sizeof(arr[0]);

    shortestSuperstringGreedy(arr, n);

    return 0;
}