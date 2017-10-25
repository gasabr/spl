#include "matrix.h"


matrix read_matrix(char* filename) {
	size_t i=0, j=0, n=0, m=0;
	float** values = NULL;
	FILE *file = fopen("a.matrix", "r");
	struct Matrix result;

	if (file == NULL)
		perror ("Error opening file");
	else
	{
		fscanf(file, "%lu %lu", &n, &m);
		values = (float **)malloc(sizeof(float *) * n);
		for (i = 0; i < n; ++i) {
			values[i] = (float *)malloc(sizeof(float) * m);
			printf("debug1\n");
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
			printf("%f ",  *(*(a.values + i) + j));
		}
		printf("\n");
	}
}
