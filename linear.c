#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linear_search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i; 
    }
    return -1; 
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; 
    }
}

int main() { 
    int n, key, pos;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n >= 8000) {
        printf("Please enter a value greater than 8000\n");
        return 1; 
    }

    // Correct allocation
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1; 
    }

    clock_t start = clock(); 
    for (int i = 0; i < 1000; i++) {
        generateRandomArray(arr, n); 
        key = arr[rand() % n];   // ✅ Now valid
        pos = linear_search(arr, n, key);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;  
    printf("Time taken to search in %d elements : %f seconds\n", n, time_taken);

    free(arr);
    return 0;
}