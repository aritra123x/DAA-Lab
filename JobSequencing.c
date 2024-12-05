#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Job {
    char id;  // Job Id
    int dead; // Deadline of job
    int profit; // Profit if job is completed within deadline
} Job;

int main() {
    Job arr[] = { { 'a', 2, 100 },
                  { 'b', 1, 19 },
                  { 'c', 2, 27 },
                  { 'd', 1, 25 },
                  { 'e', 3, 15 } };
    int n = sizeof(arr) / sizeof(arr[0]);
    Job t;
    int k = 0;
    
    // Step 1: Sort jobs by decreasing profit
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].profit < arr[j].profit) {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }

    // Step 2: Initialize result array and slot availability
    Job ans[n];  // Array to store job sequence
    bool slot[n]; // Array to keep track of used slots
    for (int i = 0; i < n; i++) {
        slot[i] = false; // Mark all slots as free initially
        ans[i].id = '\0'; // Initialize ans array with empty slots
    }

    int profit = 0; // Total profit

    // Step 3: Iterate through all jobs in sorted order
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (from its deadline backward)
        for (int j = arr[i].dead - 1; j >= 0; j--) {
            // If slot is free, assign this job to slot[j]
            if (!slot[j]) {
                ans[j] = arr[i]; // Place job in the ans array at position j
                slot[j] = true; // Mark slot as filled
                profit += arr[i].profit; // Add profit
                break; // Job placed, move to next job
            }
        }
    }

    // Step 4: Print the total profit and job sequence
    printf("Total Profit: %d\n", profit);
    printf("Job Sequence: ");
    for (int i = 0; i < n; i++) {
        if (ans[i].id != '\0') {
            printf("%c ", ans[i].id);
        }
    }
    printf("\n");

    return 0;
}
