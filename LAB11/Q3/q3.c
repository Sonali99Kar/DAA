#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100000
#define MAX_LEN 11

// Structure for Queue used in BFS
typedef struct {
    int indices[MAX_WORDS];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, int idx) {
    q->indices[q->rear++] = idx;
}

int dequeue(Queue* q) {
    return q->indices[q->front++];
}

// Comparator for sorting dictionary to enable binary search
int compareStrings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Binary search to find a word index in the sorted dictionary
int binarySearch(char dict[][MAX_LEN], int n, const char* word) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(dict[mid], word);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Bidirectional BFS to find the shortest transformation sequence length
int bidirectionalWordLadder(char dict[][MAX_LEN], int N, const char* startWord, const char* targetWord) {
    // Target must exist in dictionary
    int targetIdx = binarySearch(dict, N, targetWord);
    if (targetIdx == -1) return -1;

    // If start and target are the same
    if (strcmp(startWord, targetWord) == 0) return 0;

    // Check if start word exists in dictionary; if not, we can temporarily treat it as index -1
    int startIdx = binarySearch(dict, N, startWord);

    // Visited arrays and distance/level trackers
    // 0: Unvisited, 1: Visited by Forward search, 2: Visited by Backward search
    int* visited = (int*)calloc(N, sizeof(int));
    int* forwardDist = (int*)calloc(N, sizeof(int));
    int* backwardDist = (int*)calloc(N, sizeof(int));

    Queue qForward, qBackward;
    initQueue(&qForward);
    initQueue(&qBackward);

    // Handle start word initialization
    // If start word is not in dictionary, we can add it conceptually or handle separately. 
    // Per standard problem rules, start word might not need to be in D, but intermediate words must.
    // For simplicity, let's assume start word can connect directly to dict words.
    
    // Let's use a simpler approach: push startIdx if present, else search directly from startWord string.
    // Here, we'll enqueue startWord if found, or if not found, we handle its neighbors directly.
    if (startIdx != -1) {
        visited[startIdx] = 1;
        forwardDist[startIdx] = 0;
        enqueue(&qForward, startIdx);
    }

    visited[targetIdx] = 2;
    backwardDist[targetIdx] = 0;
    enqueue(&qBackward, targetIdx);

    int L = strlen(startWord);

    while (!isQueueEmpty(&qForward) && !isQueueEmpty(&qBackward)) {
        // Expand Forward Search Level
        int fSize = qForward.rear - qForward.front;
        for (int i = 0; i < fSize; i++) {
            int currIdx = dequeue(&qForward);
            char currWord[MAX_LEN];
            strcpy(currWord, dict[currIdx]);

            for (int j = 0; j < L; j++) {
                char originalChar = currWord[j];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == originalChar) continue;
                    currWord[j] = c;

                    int neighborIdx = binarySearch(dict, N, currWord);
                    if (neighborIdx != -1) {
                        if (visited[neighborIdx] == 2) {
                            // Intersection found!
                            int result = forwardDist[currIdx] + 1 + backwardDist[neighborIdx];
                            free(visited);
                            free(forwardDist);
                            free(backwardDist);
                            return result;
                        }
                        if (visited[neighborIdx] == 0) {
                            visited[neighborIdx] = 1;
                            forwardDist[neighborIdx] = forwardDist[currIdx] + 1;
                            enqueue(&qForward, neighborIdx);
                        }
                    }
                }
                currWord[j] = originalChar;
            }
        }

        // Expand Backward Search Level
        int bSize = qBackward.rear - qBackward.front;
        for (int i = 0; i < bSize; i++) {
            int currIdx = dequeue(&qBackward);
            char currWord[MAX_LEN];
            strcpy(currWord, dict[currIdx]);

            for (int j = 0; j < L; j++) {
                char originalChar = currWord[j];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == originalChar) continue;
                    currWord[j] = c;

                    int neighborIdx = binarySearch(dict, N, currWord);
                    if (neighborIdx != -1) {
                        if (visited[neighborIdx] == 1) {
                            // Intersection found!
                            int result = backwardDist[currIdx] + 1 + forwardDist[neighborIdx];
                            free(visited);
                            free(forwardDist);
                            free(backwardDist);
                            return result;
                        }
                        if (visited[neighborIdx] == 0) {
                            visited[neighborIdx] = 2;
                            backwardDist[neighborIdx] = backwardDist[currIdx] + 1;
                            enqueue(&qBackward, neighborIdx);
                        }
                    }
                }
                currWord[j] = originalChar;
            }
        }
    }

    free(visited);
    free(forwardDist);
    free(backwardDist);
    return -1; // No transformation sequence exists
}

int main() {
    // Example dictionary
    char dict[][MAX_LEN] = {"hot", "dot", "dog", "lot", "log", "cog"};
    int N = 6;

    char startWord[] = "hit";
    char targetWord[] = "cog";

    // Note: Dictionary should be sorted for binary search to work efficiently
    qsort(dict, N, sizeof(dict[0]), compareStrings);

    printf("Starting Bidirectional BFS Word Ladder from '%s' to '%s'\n", startWord, targetWord);
    int minMutations = bidirectionalWordLadder(dict, N, startWord, targetWord);

    if (minMutations != -1) {
        printf("Minimum number of mutations required (k): %d\n", minMutations);
    } else {
        printf("No valid transformation sequence found. Return: -1\n");
    }

    return 0;
}
