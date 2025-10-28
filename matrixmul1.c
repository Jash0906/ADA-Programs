#include <stdio.h>
#include <stdlib.h>

int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matrix[i] = (int*)malloc(n * sizeof(int));
    return matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiplyDC(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int** A11 = allocateMatrix(k);
    int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k);
    int** A22 = allocateMatrix(k);
    int** B11 = allocateMatrix(k);
    int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k);
    int** B22 = allocateMatrix(k);
    int** C11 = allocateMatrix(k);
    int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k);
    int** C22 = allocateMatrix(k);
    int** temp1 = allocateMatrix(k);
    int** temp2 = allocateMatrix(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    multiplyDC(A11, B11, temp1, k);
    multiplyDC(A12, B21, temp2, k);
    addMatrix(temp1, temp2, C11, k);
    multiplyDC(A11, B12, temp1, k);
    multiplyDC(A12, B22, temp2, k);
    addMatrix(temp1, temp2, C12, k);
    multiplyDC(A21, B11, temp1, k);
    multiplyDC(A22, B21, temp2, k);
    addMatrix(temp1, temp2, C21, k);
    multiplyDC(A21, B12, temp1, k);
    multiplyDC(A22, B22, temp2, k);
    addMatrix(temp1, temp2, C22, k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    freeMatrix(A11, k); freeMatrix(A12, k);
    freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k);
    freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(C11, k); freeMatrix(C12, k);
    freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(temp1, k); freeMatrix(temp2, k);
}

void printMatrix(int** M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d\t", M[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    multiplyDC(A, B, C, n);
    printMatrix(C, n);
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
    return 0;
}
