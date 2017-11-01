#include "matrix.h"


matrix read_matrix(const char* filename) {
	size_t i=0, j=0, n=0, m=0;
	float** values = NULL;
	FILE *file = fopen(filename, "r");
	struct Matrix result;

	if (file == NULL)
		perror ("Error opening file");
	else
	{
		fscanf(file, "%lu %lu", &n, &m);
		values = (float **)malloc(sizeof(float *) * n);
		for (i = 0; i < n; ++i) {
			values[i] = (float *)malloc(sizeof(float) * m);
			for (j = 0; j < m; ++j) {
				fscanf(file, "%f", (*(values + i) + j));
			}
		}

	}	
	result.n_columns = n;
	result.n_rows = m;
	result.values = values;
	return result;
}


void print_matrix(const matrix a) {
	size_t i, j;

	for (i = 0; i < a.n_rows; ++i) {
		for (j = 0; j < a.n_columns; ++j) {
			printf("%-7.2f ",  *(*(a.values + i) + j));
		}
		printf("\n");
	}
}


matrix matrix_sum(const matrix a, const matrix b) {
	size_t i=0, j=0;
	matrix result;
	if ((a.n_rows != b.n_rows) || (a.n_columns != b.n_columns)) {
		result.n_rows = 0;
		result.n_columns = 0;
		result.values = NULL;
		return result;
	} else {
		result.n_rows = a.n_rows;
		result.n_columns = a.n_columns;
		result.values = (float **)malloc(sizeof(float*) * result.n_rows);
		for (i=0; i<result.n_rows; ++i) {
			result.values[i] = (float *)malloc(sizeof(float) * result.n_columns);
		}
	}

	for (i=0; i<a.n_rows; ++i) {
		for (j=0; j<a.n_columns; ++j) {
			result.values[i][j] = a.values[i][j] + b.values[i][j];
		}
	}

	return result;
}


matrix matrix_sub(const matrix a, const matrix b) {
	size_t i=0, j=0;
	matrix result;
	if ((a.n_rows != b.n_rows) || (a.n_columns != b.n_columns)) {
		result.n_rows = 0;
		result.n_columns = 0;
		result.values = NULL;
		return result;
	} else {
		result.n_rows = a.n_rows;
		result.n_columns = a.n_columns;
		result.values = (float **)malloc(sizeof(float*) * result.n_rows);
		for (i=0; i<result.n_rows; ++i) {
			result.values[i] = (float *)malloc(sizeof(float) * result.n_columns);
		}
	}

	for (i=0; i<a.n_rows; ++i) {
		for (j=0; j<a.n_columns; ++j) {
			result.values[i][j] = a.values[i][j] - b.values[i][j];
		}
	}

	return result;
}


matrix matrix_mult(const matrix a, const matrix b) {
	size_t i=0, j=0, k=0;
	matrix result;
	if ((a.n_rows != b.n_columns) || (a.n_columns != b.n_rows)) {
		result.n_rows = 0;
		result.n_columns = 0;
		result.values = NULL;
		return result;
	} else {
		result.n_rows = a.n_rows;
		result.n_columns = a.n_columns;
		result.values = (float **)malloc(sizeof(float*) * result.n_rows);
		for (i=0; i<result.n_rows; ++i) {
			result.values[i] = (float *)malloc(sizeof(float) * result.n_columns);
		}
	}

	for (i=0; i<a.n_rows; ++i) {
		for (j=0; j<b.n_columns; ++j) {
			result.values[i][j] = 0;
			for (k=0; k<a.n_columns; ++k) {
				result.values[i][j] += a.values[i][k] * b.values[k][j];
			}
		}
	}
	return result;
}


bool matrix_equal(const matrix a, const matrix b) {
	size_t i=0, j=0;

	if ((a.n_rows != b.n_columns) || (a.n_columns != b.n_rows)) {
		return false;
	}
	for (i=0; i<a.n_rows; ++i) {
		for (j=0; j<a.n_columns; ++j) {
			if (a.values[i][j] != b.values[i][j]) {
				return false;
			}
		}
	}
	return true;
}
