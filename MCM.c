#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printOptimalParens(int n, int S[][n], int i, int j) {
    if (i == j) {
        printf("M%d", i + 1);
    } else {
        printf("(");
        printOptimalParens(n, S, i, S[i][j] - 1);
        printOptimalParens(n, S, S[i][j], j);
        printf(")");
    }
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    int ar[n + 1];
    int prev = -1, a = 0, b = 0, k = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter dimension 1 and dimension 2 of Matrix %d: ", i + 1);
        scanf("%d%d", &a, &b);
        if (prev == -1) {
            ar[k++] = a;
            ar[k++] = b;
            prev = b;
        } else {
            if (prev != a) {
                printf("Matrices are not compatible for multiplication!\n");
                return 1;
            }
            ar[k++] = b;
            prev = b;
        }
    }

    int M[n][n], S[n][n];  // M is the cost matrix, S is the split matrix

    // Initialize matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = 0;
            S[i][j] = 0;
        }
    }

    // Matrix Chain Multiplication Algorithm
    for (int d = 1; d < n; d++) {  
        for (int i = 0; i < n - d; i++) {
            int j = i + d;
            M[i][j] = INT_MAX;  // Set initial cost as infinity
            for (int k = i; k < j; k++) {
                int cost = M[i][k] + M[k + 1][j] + ar[i] * ar[k + 1] * ar[j + 1];
                if (cost < M[i][j]) {
                    M[i][j] = cost;
                    S[i][j] = k + 1;  // Store the split position
                }
            }
        }
    }

    // Print cost matrix M
    printf("Cost Matrix M:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", M[i][j]);
        }
        printf("\n");
    }

    // Print split matrix S
    printf("\nSplit Matrix S:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", S[i][j]);
        }
        printf("\n");
    }

    // Print the optimal parenthesization
    printf("\nOptimal Parenthesization: ");
    printOptimalParens(n, S, 0, n - 1);  // Print parentheses for matrices from M1 to Mn
    printf("\n");

    return 0;
}
