#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **makeMatrix(int n){
    int **m = (int**)malloc(n * sizeof(int*));
    for(int i=0;i<n;i++){
        m[i] = (int*)malloc(n * sizeof(int));
    }
    return m;
}

void freeMatrix(int **m, int n){
    for(int i=0;i<n;i++) free(m[i]);
    free(m);
}

void fillMatrix(int **m, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            m[i][j] = rand()%10;
        }
    }
}

void iterative(int **A,int **B,int **C,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            C[i][j]=0;
            for(int k=0;k<n;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}

void add(int **A,int **B,int **C,int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j]=A[i][j]+B[i][j];
}

void sub(int **A,int **B,int **C,int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j]=A[i][j]-B[i][j];
}

// divide and conquer
void dnc(int **A,int **B,int **C,int n){
    if(n==1){
        C[0][0]=A[0][0]*B[0][0];
        return;
    }
    int k=n/2;
    int **A11=makeMatrix(k), **A12=makeMatrix(k), **A21=makeMatrix(k), **A22=makeMatrix(k);
    int **B11=makeMatrix(k), **B12=makeMatrix(k), **B21=makeMatrix(k), **B22=makeMatrix(k);
    int **C11=makeMatrix(k), **C12=makeMatrix(k), **C21=makeMatrix(k), **C22=makeMatrix(k);
    int **P1=makeMatrix(k), **P2=makeMatrix(k), **P3=makeMatrix(k), **P4=makeMatrix(k);

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j+k];
            A21[i][j]=A[i+k][j];
            A22[i][j]=A[i+k][j+k];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+k];
            B21[i][j]=B[i+k][j];
            B22[i][j]=B[i+k][j+k];
        }
    }

    dnc(A11,B11,P1,k); dnc(A12,B21,P2,k); add(P1,P2,C11,k);
    dnc(A11,B12,P3,k); dnc(A12,B22,P4,k); add(P3,P4,C12,k);
    dnc(A21,B11,P1,k); dnc(A22,B21,P2,k); add(P1,P2,C21,k);
    dnc(A21,B12,P3,k); dnc(A22,B22,P4,k); add(P3,P4,C22,k);

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            C[i][j]=C11[i][j];
            C[i][j+k]=C12[i][j];
            C[i+k][j]=C21[i][j];
            C[i+k][j+k]=C22[i][j];
        }
    }

    freeMatrix(A11,k); freeMatrix(A12,k); freeMatrix(A21,k); freeMatrix(A22,k);
    freeMatrix(B11,k); freeMatrix(B12,k); freeMatrix(B21,k); freeMatrix(B22,k);
    freeMatrix(C11,k); freeMatrix(C12,k); freeMatrix(C21,k); freeMatrix(C22,k);
    freeMatrix(P1,k); freeMatrix(P2,k); freeMatrix(P3,k); freeMatrix(P4,k);
}

// strassen
void strassen(int **A,int **B,int **C,int n){
    if(n==1){
        C[0][0]=A[0][0]*B[0][0];
        return;
    }
    int k=n/2;
    int **A11=makeMatrix(k), **A12=makeMatrix(k), **A21=makeMatrix(k), **A22=makeMatrix(k);
    int **B11=makeMatrix(k), **B12=makeMatrix(k), **B21=makeMatrix(k), **B22=makeMatrix(k);
    int **M1=makeMatrix(k), **M2=makeMatrix(k), **M3=makeMatrix(k), **M4=makeMatrix(k);
    int **M5=makeMatrix(k), **M6=makeMatrix(k), **M7=makeMatrix(k);
    int **T1=makeMatrix(k), **T2=makeMatrix(k);
    int **C11=makeMatrix(k), **C12=makeMatrix(k), **C21=makeMatrix(k), **C22=makeMatrix(k);

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j+k];
            A21[i][j]=A[i+k][j];
            A22[i][j]=A[i+k][j+k];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+k];
            B21[i][j]=B[i+k][j];
            B22[i][j]=B[i+k][j+k];
        }
    }

    add(A11,A22,T1,k); add(B11,B22,T2,k); strassen(T1,T2,M1,k);
    add(A21,A22,T1,k); strassen(T1,B11,M2,k);
    sub(B12,B22,T1,k); strassen(A11,T1,M3,k);
    sub(B21,B11,T1,k); strassen(A22,T1,M4,k);
    add(A11,A12,T1,k); strassen(T1,B22,M5,k);
    sub(A21,A11,T1,k); add(B11,B12,T2,k); strassen(T1,T2,M6,k);
    sub(A12,A22,T1,k); add(B21,B22,T2,k); strassen(T1,T2,M7,k);

    add(M1,M4,T1,k); sub(T1,M5,T2,k); add(T2,M7,C11,k);
    add(M3,M5,C12,k);
    add(M2,M4,C21,k);
    add(M1,M3,T1,k); sub(T1,M2,T2,k); add(T2,M6,C22,k);

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            C[i][j]=C11[i][j];
            C[i][j+k]=C12[i][j];
            C[i+k][j]=C21[i][j];
            C[i+k][j+k]=C22[i][j];
        }
    }

    freeMatrix(A11,k); freeMatrix(A12,k); freeMatrix(A21,k); freeMatrix(A22,k);
    freeMatrix(B11,k); freeMatrix(B12,k); freeMatrix(B21,k); freeMatrix(B22,k);
    freeMatrix(M1,k); freeMatrix(M2,k); freeMatrix(M3,k); freeMatrix(M4,k);
    freeMatrix(M5,k); freeMatrix(M6,k); freeMatrix(M7,k);
    freeMatrix(T1,k); freeMatrix(T2,k);
    freeMatrix(C11,k); freeMatrix(C12,k); freeMatrix(C21,k); freeMatrix(C22,k);
}

int main(){
    srand(time(0));
    int sizes[] = {99, 143, 886, 969};

    for(int s=0;s<5;s++){
        int n=sizes[s];
        int **matA=makeMatrix(n), **matB=makeMatrix(n), **matC=makeMatrix(n);
        fillMatrix(matA,n); fillMatrix(matB,n);

        clock_t t1=clock();
        iterative(matA,matB,matC,n);
        clock_t t2=clock();
        printf("Iterative n=%d -> %f sec\n",n,(double)(t2-t1)/CLOCKS_PER_SEC);

        t1=clock();
        dnc(matA,matB,matC,n);
        t2=clock();
        printf("DivideConquer n=%d -> %f sec\n",n,(double)(t2-t1)/CLOCKS_PER_SEC);

        t1=clock();
        strassen(matA,matB,matC,n);
        t2=clock();
        printf("Strassen n=%d -> %f sec\n\n",n,(double)(t2-t1)/CLOCKS_PER_SEC);

        freeMatrix(matA,n); freeMatrix(matB,n); freeMatrix(matC,n);
    }
    return 0;
}
