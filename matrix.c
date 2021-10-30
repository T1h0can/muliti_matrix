#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
//    if(argc != 2) {
//        printf("arg must 1");
//        exit(1);
//    }
    int size;
//    size = atoi(argv[1]);
    printf("input size of matrix: ");
    scanf("%d", &size);
    int **mat1, **mat2;
    mat1 = (int **) malloc(sizeof(int *) * size);
    mat2 = (int **) malloc(sizeof(int *) * size);
    for(int i = 0; i < size; ++i){
        mat1[i] = (int *) malloc(sizeof(int) * size);
        mat2[i] = (int *) malloc(sizeof(int) * size);
    }
//    int mat1[size][size];
//    int mat2[size][size];
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j){
            mat1[i][j] = rand() % 100;
            mat2[i][j] = rand() % 100;
        }
    }
    for(int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", mat1[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    for(int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", mat2[i][j]);
        }
        printf("\n");
    }

    FILE *fp1 = fopen("a", "wb+");
    FILE *fp2 = fopen("b", "wb+");
    char type = 'd';
//    int32_t N = size;

    fwrite(&type, sizeof(char), 1, fp1);
    fwrite(&size, sizeof(int32_t), 1, fp1);
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            if((fwrite(&mat1[i][j], sizeof(int), 1, fp1)) == 1)
                printf("");
    fclose(fp1);

    fwrite(&type, sizeof(char), 1, fp2);
    fwrite(&size, sizeof(int32_t), 1, fp2);
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            fwrite(&mat2[i][j], sizeof(int), 1, fp2);
        }
    }
    fclose(fp2);


//    FILE *fr = fopen("c", "rb+");
//    char t;
//    int32_t n = 0;
//    fread(&t, sizeof(char), 1, fr);
//    fread(&n, sizeof(int32_t), 1, fr);

//    long mat[size][size] = {0};

//    for(int i = 0; i < n; ++i)
//        for(int j =0; j < n; ++j)
//            fread(&mat[i][j], sizeof(long), 1, fr);


//    printf("\n");
//    for(int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            printf("%ld ", mat[i][j]);
//        }
//        printf("\n");
//    }
//    fclose(fr);
    return 0;
}