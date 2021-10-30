#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "common.h"

//void readMatrixBin(char *fileNameA, long **matA, char *fileNameB, long **matB, int *size);
void readMatrixInt(FILE *fp, long **mat, int size);
void readMatrixLong(FILE *fp, long **mat, int size);
void readMatrixBin(FILE *fp, long **mat, int size, char type);
void getSizeType(FILE *fp, int *size, char *type);
long **createZeroMatrix(int size);

int main(int argc, char *argv[]) {
    FILE *fa, *fb, *fc;
//    FILE *fc;
    if(argc < 5){
        printf("arguments should more than 3\n");
        return 1;
    }
    char *fileA = argv[1];
    char *fileB = argv[2];
    char *fileC = argv[3];
    int mode = atoi(argv[4]);

    //open fileA,fileB
    if(!(fa = fopen(fileA, "rb"))) {
        printf("Can't open file %s", fileA);
        exit(1);
    }
    if(!(fb = fopen(fileB, "rb"))) {
        printf("Can't open file %s", fileB);
        exit(1);
    }
    //get size & type of matrixes
    int32_t sizeA, sizeB;
    char typeA, typeB, typeC = 'l';
    int size;

    getSizeType(fa, &sizeA, &typeA);
    getSizeType(fb, &sizeB, &typeB);

    if(sizeA != sizeB) {
        printf("size of matrixes is different!\n");
        exit(1);
    } else
        size = sizeA;

    long **matA;
    long **matB;
    long **matC;

    matA = (long**) malloc(sizeof (long *) * size);
    matB = (long**) malloc(sizeof (long *) * size);
    matC = (long**) malloc(sizeof (long *) * size);
    for(int i = 0; i < size; ++i){
        matA[i] = (long *) malloc(sizeof(long) * size);
        matB[i] = (long *) malloc(sizeof(long) * size);
        matC[i] = (long *) malloc(sizeof(long) * size);
    }

    //read matrixA & matrixB
    readMatrixBin(fa, matA, size, typeA);
    fclose(fa);
    readMatrixBin(fb, matB, size, typeB);
    fclose(fb);

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            matC[i][j] = 0;

    printf("matrix A\n");
    printMatrix(matA, size);
    printf("matrix B\n");
    printMatrix(matB, size);
    printf("matrix C\n");
    printMatrix(matC, size);

    struct timespec ts1, ts2;
    double dt; /* seconds */
    clock_gettime(CLOCK_REALTIME, &ts1);


    switch (mode) {
        case 0:
            ijk(sizeA, matA, matB, matC);
            break;
        case 1:
            ikj(sizeA, matA, matB, matC);
            break;
        case 2:
            kij(sizeA, matA, matB, matC);
            break;
        case 3:
            jik(sizeA, matA, matB, matC);
            break;
        case 4:
            jki(sizeA, matA, matB, matC);
            break;
        case 5:
            kji(sizeA, matA, matB, matC);
            break;

        default:
            return 1;
    }

    clock_gettime(CLOCK_REALTIME, &ts2);

    dt = (double) (ts2.tv_sec - ts1.tv_sec) +
         (double) ts2.tv_nsec / (1000.0*1000.0*1000.0) -
         (double) ts1.tv_nsec / (1000.0*1000.0*1000.0);

    fc = fopen("c", "wb+");
    fwrite(&typeC, sizeof(char), 1, fc);
    fwrite(&size, sizeof(int32_t), 1, fc);
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            fwrite(&matC[i][j], sizeof(long), 1, fc);

    printf("matrix C\n");
    printMatrix(matC, size);

    printf("time = %f\n", dt);

    return 0;
}

void getSizeType(FILE *fp, int *size, char *type) {
    char _t;
    int32_t _n;
    if(fread(&_t, sizeof(char), 1, fp) != 1) {
        printf("error when read type\n");
        exit(1);
    }
    if(fread(&_n, sizeof(int32_t), 1, fp) != 1) {
        printf("error when read N\n");
        exit(1);
    }
    *size = _n;
    *type = _t;
}
void readMatrixBin(FILE *fp, long **mat, int size, char type) {
    if(type == 'd')
        readMatrixInt(fp, mat, size);
    if(type == 'l')
        readMatrixLong(fp, mat, size);
}

void readMatrixInt(FILE *fp, long **mat,  int size) {
    int x;
    for(int i = 0; i < size; ++i)
        for(int j =0; j < size; ++j) {
            if(fread(&x, sizeof(int),1, fp) != 1)
                printf("error when read matrix[%d][%d]", i, j);
            mat[i][j] = (long)x;
        }
}

void readMatrixLong(FILE *fp, long **mat, int size) {
    for(int i = 0; i < size; ++i)
        for(int j =0; j < size; ++j)
            if(fread(&mat[i][j], sizeof(long),1, fp) != 1)
                printf("error when read matrix[%d][%d]", i, j);
}


//void readMatrixBin(char *fileNameA, long **matA, char *fileNameB, long **matB, int *size) {
//    FILE *fa;
//    if(!(fa = fopen(fileNameA, "rb"))) {
//        printf("Can't open file %s", fileNameA);
//        exit(1);
//    }
//    char type;
//    if((fread(&type, sizeof(char), 1, fa)) != 1){
//        printf("error when read type\n");
//        exit(1);
//    }
//    int32_t N;
//    if((fread(&N, sizeof(int32_t), 1, fa)) != 1) {
//        printf("error when read N\n");
//        exit(1);
//    }
//    *size = N;
//
//}

long **createZeroMatrix(int size) {
    long ** _mat = (long **) malloc(sizeof(long *) * size);
    for(int i = 0; i < size; ++i)
        _mat[i] = (long *) malloc(sizeof(long) * size);
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            _mat[i][j] = 0;
    return _mat;
}
