#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct pair {
    int weight;
    int node;    
};

void swap(struct pair *a, struct pair *b) {
    struct pair tmp = *a;
    *a = *b;
    *b = tmp;
}

void minHeapify(struct pair arr[], int N, int i) {
    int min = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < N && arr[l].weight < arr[min].weight)
        min = l;
    if (r < N && arr[r].weight < arr[min].weight)
        min = r;
    
    if (min != i) {
        swap(&arr[i], &arr[min]);
        minHeapify(arr, N, min);
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
        return (struct pair){-1, -1};
    }

    struct pair min = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;

    minHeapify(heap, *size, 0);
    
    return min;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j + 1);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j + 1);
}

int main() {
    struct pair minheap[100];
    int size = 0;
    FILE *ptr;
    int n = 0, s = 0;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter source vertex: ");
    scanf("%d", &s);

    int ar[n][n];

    ptr = fopen("C:\\Users\\KIIT\\OneDrive\\Desktop\\Resources\\5th\\DAA\\DAA Lab\\Lab 7\\Read.txt", "r");
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
            printf("%d\t", ar[i][j]);
        }
        printf("\n");
    }

    int dist[n];
    int visited[n];
    int parent[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;  
        visited[i] = 0;    
        parent[i] = -1;   
    }
    dist[s - 1] = 0;     

    
    struct pair newPair;
    newPair.node = s - 1;
    newPair.weight = 0;
    insert(minheap, newPair, &size);

    while (size > 0) {
        struct pair min = deleteMin(minheap, &size);
        int u = min.node;

        if (visited[u]) continue;
        visited[u] = 1;

        for (int i = 0; i < n; i++) {
            if (ar[u][i] != 0 && !visited[i]) {
                int newDist = dist[u] + ar[u][i];
                if (newDist < dist[i]) {
                    dist[i] = newDist;
                    parent[i] = u;
                    struct pair add;
                    add.node = i;
                    add.weight = newDist;
                    insert(minheap, add, &size);
                }
            }
        }
    }

    printf("Shortest distances and paths from source vertex %d:\n", s);
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: Distance = ", i + 1);
        if (dist[i] == INT_MAX) {
            printf("INF, Path = None\n");
        } else {
            printf("%d, Path = ", dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }

    return 0;
}
