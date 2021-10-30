CC = gcc

Matrix: multi_matrix.c common.h common.c
	$(CC) -o Matrix multi_matrix.c common.c -lm

createMatrix: matrix.c
	$(CC) -o createMatrix matrix.c

clean:
	rm Matrix
