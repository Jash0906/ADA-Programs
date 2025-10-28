#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
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
    if (n <=0) {
        printf("Please enter a positive value number\n");
        return 1; 
    }
    // allocation
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1; 
    }
    clock_t start = clock(); 
    for (int i = 0; i < 1000; i++) {
        generateRandomArray(arr, n); 
        key = arr[rand() % n]; 
        pos = binarySearch(arr, n, key);
    }
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;  
    printf("Time taken to search in %d elements : %f seconds\n", n, time_taken);
    free(arr);
    return 0;
}
