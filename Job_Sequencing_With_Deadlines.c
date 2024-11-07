#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
typedef struct {
    int id;     
    int dead;     
    int profit; 
} Job;
int compare(const void *a, const void *b) {
    return ((Job*)b)->profit - ((Job*)a)->profit;
}
void jobSequencing(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);
    int result[MAX]; 
    bool slot[MAX];   
    for (int i = 0; i < n; i++) {
        slot[i] = false;
    }
    for (int i = 0; i < n; i++) {
        result[i] = -1;
    }
    int totalProfit = 0; 
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].dead - 1; j >= 0; j--) {
            if (slot[j] == false) {
                result[j] = jobs[i].id;
                slot[j] = true;
                totalProfit += jobs[i].profit;  
                break;
            }
        }
    }
    printf("\nJob sequence (Job IDs): ");
    for (int i = 0; i < n; i++) {
        if (result[i] != -1) {
            printf("%d ", result[i]);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);  
}
int main() {
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX) {
        printf("Invalid number of jobs. Exiting program.\n");
        return -1;
    }
    Job jobs[n];  
    printf("Enter job details (id, deadline, profit):\n");
    for (int i = 0; i < n; i++) {
        printf("Job %d (ID, Deadline, Profit): ", i + 1);
        scanf("%d %d %d", &jobs[i].id, &jobs[i].dead, &jobs[i].profit);
    }
    jobSequencing(jobs, n);
    return 0;
}
