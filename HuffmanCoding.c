#include <stdio.h>
#include <stdlib.h>

typedef struct SYMBOL {
    char alphabet;
    int frequency;
} SYMBOL;

typedef struct Node {
    SYMBOL symbol;
    struct Node *left, *right;
} Node;

Node* createNode(char alphabet, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->symbol.alphabet = alphabet;
    newNode->symbol.frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void swapNodes(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(Node** array, int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && array[left]->symbol.frequency < array[smallest]->symbol.frequency)
        smallest = left;

    if (right < size && array[right]->symbol.frequency < array[smallest]->symbol.frequency)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&array[smallest], &array[idx]);
        minHeapify(array, size, smallest);
    }
}

Node* extractMin(Node** array, int* size) {
    Node* temp = array[0];
    array[0] = array[*size - 1];
    --(*size);
    minHeapify(array, *size, 0);
    return temp;
}

void insertMinHeap(Node** array, int* size, Node* newNode) {
    ++(*size);
    int i = *size - 1;

    while (i && newNode->symbol.frequency < array[(i - 1) / 2]->symbol.frequency) {
        array[i] = array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    array[i] = newNode;
}

void buildMinHeap(Node** array, int size) {
    for (int i = (size - 2) / 2; i >= 0; --i)
        minHeapify(array, size, i);
}



Node* buildHuffmanTree(SYMBOL symbols[], int size) {
    Node* array[size];
    int heapSize = size;

    for (int i = 0; i < size; ++i)
        array[i] = createNode(symbols[i].alphabet, symbols[i].frequency);

    buildMinHeap(array, heapSize);

    while (heapSize > 1) {
        Node* left = extractMin(array, &heapSize);
        Node* right = extractMin(array, &heapSize);
        Node* top = createNode('$', left->symbol.frequency + right->symbol.frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(array, &heapSize, top);
    }
    return extractMin(array, &heapSize);
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        if (root->symbol.alphabet != '$') {
            printf("%c ", root->symbol.alphabet);
        }
        inorderTraversal(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    SYMBOL symbols[n];
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; ++i) {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &symbols[i].frequency);
    }

    Node* root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
