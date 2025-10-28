#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplyIterative(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int **allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n * sizeof(int));
    return matrix;
}

void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

int main() {
    int sizes[] = {99, 143, 886, 969};
    int numSizes = 4;

    srand(time(NULL));

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }

        clock_t start = clock();
        multiplyIterative(A, B, C, n);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Iterative | Size = %d | Time = %f seconds\n", n, time_taken);

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }

    return 0;
}
