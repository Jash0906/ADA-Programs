#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

int **allocateMatrix(int n) {
 
int **matrix = (int **)malloc(n * sizeof(int *)); for (int i = 0; i < n; i++)
matrix[i] = (int *)malloc(n * sizeof(int)); return matrix;
}


void freeMatrix(int **matrix, int n) { for (int i = 0; i < n; i++) free(matrix[i]); free(matrix);
}


void addMatrix(int **A, int **B, int **C, int n) { for (int i = 0; i < n; i++)
for (int j = 0; j < n; j++)
C[i][j] = A[i][j] + B[i][j];
}


void subMatrix(int **A, int **B, int **C, int n) { for (int i = 0; i < n; i++)
for (int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
}


void multiplyRecursive(int **A, int **B, int **C, int n) { if (n == 1) {
C[0][0] = A[0][0] * B[0][0];
return;
}
 
int k = n / 2;
int **A11 = allocateMatrix(k); int **A12 = allocateMatrix(k); int **A21 = allocateMatrix(k); int **A22 = allocateMatrix(k); int **B11 = allocateMatrix(k); int **B12 = allocateMatrix(k); int **B21 = allocateMatrix(k); int **B22 = allocateMatrix(k); int **C11 = allocateMatrix(k); int **C12 = allocateMatrix(k); int **C21 = allocateMatrix(k); int **C22 = allocateMatrix(k);
int **temp1 = allocateMatrix(k); int **temp2 = allocateMatrix(k);


for (int i = 0; i < k; i++) { for (int j = 0; j < k; j++) {
A11[i][j] = A[i][j];
A12[i][j] = A[i][j+k];
A21[i][j] = A[i+k][j];
A22[i][j] = A[i+k][j+k];


B11[i][j] = B[i][j];
B12[i][j] = B[i][j+k];
B21[i][j] = B[i+k][j];
B22[i][j] = B[i+k][j+k];
}
}


multiplyRecursive(A11, B11, temp1, k); multiplyRecursive(A12, B21, temp2, k); addMatrix(temp1, temp2, C11, k);

multiplyRecursive(A11, B12, temp1, k); multiplyRecursive(A12, B22, temp2, k);
 
addMatrix(temp1, temp2, C12, k);


multiplyRecursive(A21, B11, temp1, k); multiplyRecursive(A22, B21, temp2, k); addMatrix(temp1, temp2, C21, k);

multiplyRecursive(A21, B12, temp1, k); multiplyRecursive(A22, B22, temp2, k); addMatrix(temp1, temp2, C22, k);

for (int i = 0; i < k; i++)
for (int j = 0; j < k; j++) { C[i][j]	= C11[i][j];
C[i][j+k]	= C12[i][j];
C[i+k][j]	= C21[i][j];
C[i+k][j+k] = C22[i][j];
}


freeMatrix(A11,k); freeMatrix(A12,k); freeMatrix(A21,k); freeMatrix(A22,k); freeMatrix(B11,k); freeMatrix(B12,k); freeMatrix(B21,k); freeMatrix(B22,k); freeMatrix(C11,k); freeMatrix(C12,k); freeMatrix(C21,k); freeMatrix(C22,k); freeMatrix(temp1,k); freeMatrix(temp2,k);
}


int main() {
int sizes[] = {99, 143, 365}; 
int numSizes = 3;

srand(time(NULL));
 
for (int s = 0; s < numSizes; s++) { int n = sizes[s];
int **A = allocateMatrix(n); int **B = allocateMatrix(n); int **C = allocateMatrix(n);

for (int i = 0; i < n; i++)
for (int j = 0; j < n; j++) { A[i][j] = rand() % 10;
B[i][j] = rand() % 10;
}


clock_t start = clock(); multiplyRecursive(A, B, C, n); clock_t end = clock();

double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; printf("Recursive | Size = %d | Time = %f seconds\n", n, time_taken);

freeMatrix(A, n); freeMatrix(B, n); freeMatrix(C, n);
}
return 0;
} 
