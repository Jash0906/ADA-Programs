#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        int temp = arr[min]; arr[min] = arr[i]; arr[i] = temp;
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
        selectionSort(temp, n);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) / repeats;
    printf("Selection Sort completed in %f seconds (average)\n", time_taken);

    free(arr);
    free(temp);
    return 0;
}
