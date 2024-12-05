#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int edge[][3], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edge[j][2] > edge[j + 1][2]) {
                int temp0 = edge[j][0];
                int temp1 = edge[j][1];
                int temp2 = edge[j][2];

                edge[j][0] = edge[j + 1][0];
                edge[j][1] = edge[j + 1][1];
                edge[j][2] = edge[j + 1][2];

                edge[j + 1][0] = temp0;
                edge[j + 1][1] = temp1;
                edge[j + 1][2] = temp2;
            }
        }
    }
}


void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}


int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[], int n)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskalAlgo(int n, int edge[][3])
{
    bubbleSort(edge, n);

    int parent[n];
    int rank[n];

    makeSet(parent, rank, n);

    int minCost = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < n; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main()
{
    int n = 0, m = 0;
    printf("Enter the number of vertices and edges\n");
    scanf("%d%d", &m, &n);

    int edge[n][3];
    printf("Enter each edge as u v weight\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++)
            scanf("%d", &edge[i][j]);
    }

    kruskalAlgo(n, edge);

    return 0;
}
