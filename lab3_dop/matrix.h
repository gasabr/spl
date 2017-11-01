#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Matrix {
	size_t n_rows;
	size_t n_columns;
	float** values;
} matrix;

matrix read_matrix(const char* filename);
void print_matrix(const matrix m);
matrix matrix_sum(const matrix a, const matrix b);
matrix matrix_sub(const matrix a, const matrix b);
matrix matrix_mult(const matrix a, const matrix b);
bool matrix_equal(const matrix a, const matrix b);
