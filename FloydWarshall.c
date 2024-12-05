#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

void printPath(int next[][100], int i, int j) {
    if (next[i][j] == -1) {
        printf("No path\n");
        return;
    }

    printf("Path: %d ", i + 1);
    while (i != j) {
        i = next[i][j];
        printf("-> %d ", i + 1);
    }
    printf("\n");
}

int main() {
    FILE *ptr;
    int n = 0, a = 0, b = 0;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the source and destination vertex: ");
    scanf("%d%d", &a, &b);

    int ar[n][n];
    int next[100][100];

    ptr = fopen("C:\\Users\\KIIT\\OneDrive\\Desktop\\Resources\\5th\\DAA\\DAA Lab\\Lab 9\\Read.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(ptr, "%d", &ar[i][j]);
            if (ar[i][j] == 0 && i != j) {
                ar[i][j] = INT_MAX; 
            }
            next[i][j] = (ar[i][j] == INT_MAX) ? -1 : j; 
        }
    }
    fclose(ptr);

    
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ar[i][j] == INT_MAX) {
                printf("INF\t");
            } else {
                printf("%d\t", ar[i][j]);
            }
        }
        printf("\n");
    }

    
    for (int k = 0; k < n; k++) { 
        for (int i = 0; i < n; i++) {  
            for (int j = 0; j < n; j++) {  
                if (ar[i][k] != INT_MAX && ar[k][j] != INT_MAX && ar[i][j] > ar[i][k] + ar[k][j]) {
                    ar[i][j] = ar[i][k] + ar[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    printf("Output Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ar[i][j] == INT_MAX) {
                printf("INF\t");
            } else {
                printf("%d\t", ar[i][j]);
            }
        }
        printf("\n");
    }

    printf("Shortest Distance from %d to %d: ", a, b);
    if (ar[a - 1][b - 1] == INT_MAX) {
        printf("INF (No path exists)\n");
    } else {
        printf("%d\n", ar[a - 1][b - 1]);
        printPath(next, a - 1, b - 1);
    }

    return 0;
}
