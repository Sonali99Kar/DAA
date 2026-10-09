#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MinHeapNode {
    char data;
    unsigned frequency;
    int length; // Bit length of the Huffman code
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

// Create a new node
struct MinHeapNode* newNode(char data, unsigned frequency) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->left = node->right = NULL;
    node->data = data;
    node->frequency = frequency;
    node->length = 0;
    return node;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Calculate code lengths from Huffman tree
void calculateLengths(struct MinHeapNode* root, int len) {
    if (!root) return;
    if (!root->left && !root->right) {
        root->length = len;
        return;
    }
    calculateLengths(root->left, len + 1);
    calculateLengths(root->right, len + 1);
}

// Store leaf nodes for sorting
struct SymbolInfo {
    char data;
    int freq;
    int length;
};

void collectLeaves(struct MinHeapNode* root, struct SymbolInfo symbols[], int* idx) {
    if (!root) return;
    if (!root->left && !root->right) {
        symbols[*idx].data = root->data;
        symbols[*idx].freq = root->frequency;
        symbols[*idx].length = root->length;
        (*idx)++;
        return;
    }
    collectLeaves(root->left, symbols, idx);
    collectLeaves(root->right, symbols, idx);
}

int compareSymbols(const void* a, const void* b) {
    struct SymbolInfo* s1 = (struct SymbolInfo*)a;
    struct SymbolInfo* s2 = (struct SymbolInfo*)b;
    if (s1->length != s2->length)
        return s1->length - s2->length;
    return s1->data - s2->data;
}

void generateCanonicalCodes(struct SymbolInfo symbols[], int n) {
    char code[32] = {0};
    int current_length = symbols[0].length;
    
    // Initialize first code with zeros of given length
    for (int i = 0; i < current_length; i++) code[i] = '0';
    code[current_length] = '\0';

    printf("\n--- Canonical Huffman Codebook ---\n");
    printf("Symbol\tFreq\tLength\tCanonical Code\n");
    printf("----------------------------------------\n");
    printf("%c\t%d\t%d\t%s\n", symbols[0].data, symbols[0].freq, symbols[0].length, code);

    for (int i = 1; i < n; i++) {
        // Increment binary code string
        int val = strtol(code, NULL, 2) + 1;
        int diff = symbols[i].length - current_length;
        val <<= diff;
        current_length = symbols[i].length;

        // Convert back to binary string of length current_length
        for (int j = current_length - 1; j >= 0; j--) {
            code[j] = (val & 1) ? '1' : '0';
            val >>= 1;
        }
        code[current_length] = '\0';

        printf("%c\t%d\t%d\t%s\n", symbols[i].data, symbols[i].freq, symbols[i].length, code);
    }
}

int main() {
    int n;
    printf("Enter number of symbols: ");
    if (scanf("%d", &n) != 1) return 1;

    char* data = (char*)malloc(n * sizeof(char));
    int* freq = (int*)malloc(n * sizeof(int));

    printf("Enter symbol and its frequency (e.g., A 5):\n");
    for (int i = 0; i < n; i++) {
        printf("Symbol %d: ", i + 1);
        scanf(" %c %d", &data[i], &freq[i]);
    }

    struct MinHeapNode* root = buildHuffmanTree(data, freq, n);
    calculateLengths(root, 0);

    struct SymbolInfo* symbols = (struct SymbolInfo*)malloc(n * sizeof(struct SymbolInfo));
    int idx = 0;
    collectLeaves(root, symbols, &idx);

    qsort(symbols, n, sizeof(struct SymbolInfo), compareSymbols);
    generateCanonicalCodes(symbols, n);

    free(data);
    free(freq);
    free(symbols);
    return 0;
}