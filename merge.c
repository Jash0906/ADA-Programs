#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
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
        mergeSort(temp, 0, n - 1);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) / repeats;
    printf("Merge Sort completed in %f seconds (average)\n", time_taken);

    free(arr);
    free(temp);
    return 0;
}
