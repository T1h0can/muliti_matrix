#include "common.h"

void ijk(int N, long** A, long** B, long** C){
    for (int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            int sum = 0;
            for (int k = 0; k<N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}

void jik(int N, long **A, long **B, long **C){
    for(int j=0; j<N; ++j){
        for (int i=0; i<N; ++i){
            int sum = 0;
            for (int k = 0; k<N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}

void ikj(int N, long **A, long **B, long **C){
    for (int i=0; i<N; ++i){
        for(int k=0; k<N; k++){
            int r = A[i][k];
            for (int j = 0; j<N; ++j)
                C[i][j] += r * B[k][j];
        }
    }
}

void jki(int N, long **A, long **B, long **C){
    for (int j = 0; j<N; ++j){
        for(int k=0; k<N; k++){
            int r = B[k][j];
            for (int i=0; i<N; ++i)
                C[i][j] += A[i][k] * r;
        }
    }
}

void kji(int N, long **A, long **B, long **C){
    for(int k=0; k<N; k++){
        for (int j = 0; j<N; ++j){
            int r = B[k][j];
            for (int i=0; i<N; ++i)
                C[i][j] += A[i][k] * r;
        }
    }
}

void kij(int N, long **A, long **B, long **C){
    for(int k=0; k<N; k++){
        for (int i=0; i<N; ++i){
            int r = A[i][k];
            for (int j = 0; j<N; ++j)
                C[i][j] += B[k][j] * r;
        }
    }
}

void printMatrix(long **matrix, int size) {
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j)
            printf("%ld ", matrix[i][j]);
        printf("\n");
    }
}