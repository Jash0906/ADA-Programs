#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a square matrix
int** allocateMatrix(int n) {
    int** matrix = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        matrix[i] = (int*)malloc(n * sizeof(int));
    return matrix;
}

// Function to add two matrices
void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Divide and Conquer multiplication
void multiplyDC(int** A, int** B, int** C, int n) {
    if (n == 1) { // Base case: 1x1 matrix
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Allocate submatrices
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

    // Divide matrices A and B into quadrants
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

    // C11 = A11*B11 + A12*B21
    multiplyDC(A11, B11, temp1, k);
    multiplyDC(A12, B21, temp2, k);
    addMatrix(temp1, temp2, C11, k);

    // C12 = A11*B12 + A12*B22
    multiplyDC(A11, B12, temp1, k);
    multiplyDC(A12, B22, temp2, k);
    addMatrix(temp1, temp2, C12, k);

    // C21 = A21*B11 + A22*B21
    multiplyDC(A21, B11, temp1, k);
    multiplyDC(A22, B21, temp2, k);
    addMatrix(temp1, temp2, C21, k);

    // C22 = A21*B12 + A22*B22
    multiplyDC(A21, B12, temp1, k);
    multiplyDC(A22, B22, temp2, k);
    addMatrix(temp1, temp2, C22, k);

    // Combine quadrants into result matrix C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

// Print a matrix
void printMatrix(int** M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d\t", M[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter matrix size (n x n, power of 2): ");
    scanf("%d", &n);

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    multiplyDC(A, B, C, n);

    printf("Resultant Matrix:\n");
    printMatrix(C, n);

    return 0;
}