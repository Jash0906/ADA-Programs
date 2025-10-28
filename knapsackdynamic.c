#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack01(int W, int wt[], int val[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = (int *)malloc((W + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    int res = dp[n][W];
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
    return res;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    int *val = (int*)malloc(n * sizeof(int));
    int *wt = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight of item %d: ", i + 1);
        scanf("%d %d", &val[i], &wt[i]);
    }
    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);

    clock_t start, end;
    start = clock();
    int result = knapsack01(W, wt, val, n);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    size_t space_used = (n + 1) * (W + 1) * sizeof(int);

    printf("\n0/1 Knapsack Result:\n");
    printf("Maximum Value: %d\n", result);
    printf("Time Taken: %.6f seconds\n", time_taken);
    printf("Approx. Space Used: %zu bytes\n", space_used);

    free(val);
    free(wt);
    return 0;
}
