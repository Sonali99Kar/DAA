#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a character and its frequency
typedef struct {
    char ch;
    int count;
} CharFreq;

// Max-Heap structure for frequencies
typedef struct {
    CharFreq* arr;
    int size;
    int capacity;
} MaxHeap;

// Queue structure for K-distance cooldown
typedef struct {
    CharFreq* arr;
    int* available_time;
    int front, rear, capacity;
} CooldownQueue;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (CharFreq*)malloc(capacity * sizeof(CharFreq));
    return heap;
}

void swap(CharFreq* a, CharFreq* b) {
    CharFreq temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapInsert(MaxHeap* heap, CharFreq item) {
    int i = heap->size++;
    heap->arr[i] = item;

    while (i != 0 && heap->arr[(i - 1) / 2].count < heap->arr[i].count) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void maxHeapify(MaxHeap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left].count > heap->arr[largest].count)
        largest = left;
    if (right < heap->size && heap->arr[right].count > heap->arr[largest].count)
        largest = right;

    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        maxHeapify(heap, largest);
    }
}

CharFreq extractMax(MaxHeap* heap) {
    CharFreq root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    maxHeapify(heap, 0);
    return root;
}

// Function to rearrange the string
char* reorganizeString(char* s, int k) {
    int len = strlen(s);
    if (k <= 1) {
        char* res = (char*)malloc((len + 1) * sizeof(char));
        strcpy(res, s);
        return res;
    }

    int freq[26] = {0};
    for (int i = 0; i < len; i++) {
        freq[s[i] - 'a']++;
    }

    MaxHeap* heap = createMaxHeap(26);
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            maxHeapInsert(heap, (CharFreq){'a' + i, freq[i]});
        }
    }

    char* result = (char*)malloc((len + 1) * sizeof(char));
    int resIndex = 0;

    // Cooldown queue to store elements waiting for K-distance
    CharFreq* waitQueue = (CharFreq*)malloc(len * sizeof(CharFreq));
    int* waitTime = (int*)malloc(len * sizeof(int));
    int qFront = 0, qRear = 0;

    for (int i = 0; i < len; i++) {
        // Check if any element in the wait queue has finished its K-distance cooldown
        if (qFront < qRear && waitTime[qFront] <= i) {
            maxHeapInsert(heap, waitQueue[qFront++]);
        }

        if (heap->size == 0) {
            free(result);
            free(heap->arr);
            free(heap);
            free(waitQueue);
            free(waitTime);
            return strdup(""); // Impossible to form
        }

        CharFreq current = extractMax(heap);
        result[resIndex++] = current.ch;
        current.count--;

        // If characters are still left, push to cooldown queue
        if (current.count > 0) {
            waitQueue[qRear] = current;
            waitTime[qRear++] = i + k;
        }
    }

    result[resIndex] = '\0';

    free(heap->arr);
    free(heap);
    free(waitQueue);
    free(waitTime);
    return result;
}

int main() {
    char s[] = "aabbcc";
    int k = 3;

    char* rearranged = reorganizeString(s, k);
    if (strlen(rearranged) > 0)
        printf("Rearranged string: %s\n", rearranged);
    else
        printf("Empty string (Rearrangement impossible).\n");

    free(rearranged);
    return 0;
}