#include<stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n = 0, m = 0;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity of knapsack: ");
    scanf("%d", &m);
    
    int weight[n], profit[n];
    for(int i = 0; i < n; i++) {
        printf("Enter weight and profit of Item %d: ", i + 1);
        scanf("%d %d", &weight[i], &profit[i]);
    }

    int mem[n + 1][m + 1];

    
    for(int j = 0; j <= m; j++) {
        mem[0][j] = 0;
    }

    
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            if(j >= weight[i - 1]) {
                mem[i][j] = max(mem[i - 1][j], mem[i - 1][j - weight[i - 1]] + profit[i - 1]);
            } else {
                mem[i][j] = mem[i - 1][j];
            }
        }
    }

    // Print the DP table
    printf("\nDP Table:\n");
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            printf("%d ", mem[i][j]);
        }
        printf("\n");
    }

    // The maximum profit is in mem[n][m]
    printf("\nMax Profit: %d\n", mem[n][m]);

    // Backtracking to find which items were included in the solution
    printf("Items included in the knapsack:\n");
    int totalProfit = mem[n][m];
    int w = m;  // Start with the full capacity
    for(int i = n; i > 0 && totalProfit > 0; i--) {
        // If the profit comes from including item i-1
        if(totalProfit != mem[i-1][w]) {
            printf("Item %d (Weight: %d, Profit: %d)\n", i, weight[i-1], profit[i-1]);
            totalProfit -= profit[i-1];  // Subtract the profit of the included item
            w -= weight[i-1];  // Decrease the remaining weight capacity
        }
    }

    return 0;
}
