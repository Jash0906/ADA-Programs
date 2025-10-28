#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item {
    int weight;
    int value;
};

int compare(const void *a, const void *b) {
    double r1 = (double)((struct Item*)a)->value / ((struct Item*)a)->weight;
    double r2 = (double)((struct Item*)b)->value / ((struct Item*)b)->weight;
    return r2 > r1 ? 1 : -1;
}

double fractionalKnapsack(int W, struct Item arr[], int n) {
    qsort(arr, n, sizeof(arr[0]), compare);
    int curWeight = 0;
    double finalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (curWeight + arr[i].weight <= W) {
            curWeight += arr[i].weight;
            finalValue += arr[i].value;
        } else {
            int remain = W - curWeight;
            finalValue += arr[i].value * ((double) remain / arr[i].weight);
            break;
        }
    }
    return finalValue;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    struct Item *arr = (struct Item*)malloc(n * sizeof(struct Item));
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight of item %d: ", i + 1);
        scanf("%d %d", &arr[i].value, &arr[i].weight);
    }
    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);

    clock_t start, end;
    start = clock();
    double result = fractionalKnapsack(W, arr, n);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    size_t space_used = sizeof(struct Item) * n;

    printf("\nFractional Knapsack Result:\n");
    printf("Maximum Value: %.2f\n", result);
    printf("Time Taken: %.6f seconds\n", time_taken);
    printf("Approx. Space Used: %zu bytes\n", space_used);

    free(arr);
    return 0;
}
