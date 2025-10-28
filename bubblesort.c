#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    int *temp = (int*)malloc(n * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < n; i++) arr[i] = rand() % 1000;

    int repeats = 10000;
    clock_t start = clock();
    for (int r = 0; r < repeats; r++) {
        for (int i = 0; i < n; i++) temp[i] = arr[i];
        bubbleSort(temp, n);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) / repeats;
    printf("Bubble Sort completed in %f seconds (average)\n", time_taken);

    free(arr);
    free(temp);
    return 0;
}
