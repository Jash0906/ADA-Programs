#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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
        insertionSort(temp, n);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) / repeats;
    printf("Insertion Sort completed in %f seconds (average)\n", time_taken);

    free(arr);
    free(temp);
    return 0;
}
