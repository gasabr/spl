#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix {
	size_t n_rows;
	size_t n_columns;
	float** values;
} matrix;

matrix read_matrix(char* filename);
void print_matrix(matrix m);
