#include <stdio.h>
#include <stdlib.h>

struct pair {
    int u;
    int v;
    int weight;   
};

void swap(struct pair *a, struct pair *b) {
    struct pair temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct pair heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].weight < heap[smallest].weight) {
        smallest = left;
    }
    if (right < size && heap[right].weight < heap[smallest].weight) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}


void insert(struct pair heap[], struct pair newPair, int *size) {
    heap[*size] = newPair;
    int i = *size;
    (*size)++;

    
    while (i != 0 && heap[(i - 1) / 2].weight > heap[i].weight) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


struct pair deleteMin(struct pair heap[], int *size) {
    if (*size <= 0) {
        printf("Heap is empty!\n");
        return (struct pair){-1, -1, -1};
    }

    struct pair min = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    
    minHeapify(heap, *size, 0);
    
    return min;
}

int main() {
    FILE *ptr;
    int n = 0;
    int capacity = 100;
    struct pair heap[capacity];
    int size = 0;

    printf("Enter the number of vertices: \n");
    scanf("%d", &n);

    int ar[n][n];
    int out[n][n];
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            out[i][j] = 0;
        }
    }

    ptr = fopen("C:\\Users\\KIIT\\OneDrive\\Desktop\\Resources\\5th\\DAA\\DAA Lab\\Lab 6\\Read.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(ptr, "%d", &ar[i][j]);
        }
    }
    fclose(ptr);

    printf("Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", ar[i][j]);
        }
        printf("\n");
    }
    int s=0;
	printf("Enter starting vetex : ");
	scanf("%d",&s);
    int sum = 0;
    struct pair newPair;
    newPair.u = s-1;
    newPair.v = s-1;
    newPair.weight = 0;
    insert(heap, newPair, &size);

    while (size > 0) {
        newPair = deleteMin(heap, &size);
        int u = newPair.u;
        int v = newPair.v;
        int wt = newPair.weight;

        if (visited[u] == 1) {
            continue;
        }

        visited[u] = 1;
        sum += wt;

        if (u != v) { 
            out[u][v] = wt;
            out[v][u] = wt;
        }

        for (int i = 0; i < n; i++) {
            if (visited[i] == 0 && ar[u][i] != 0) { 
                struct pair edge;
                edge.u = i;
                edge.v = u;
                edge.weight = ar[u][i];
                insert(heap, edge, &size);
            }
        }
    }

    printf("Sum of weights in the Minimum Spanning Tree: %d\n", sum);

    // Output the MST adjacency matrix
    printf("MST Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", out[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
