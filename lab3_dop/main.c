#include "main.h"


// couple of dumb tests
bool test() {
	matrix a = read_matrix("a.matrix");
	matrix b = read_matrix("b.matrix");
	matrix c = matrix_sum(a, b);
	if (!matrix_equal(c, read_matrix("sum.matrix"))) {
		printf("sum test failed!\n");
		return false;
	}

	c = matrix_sub(a, b);
	if (!matrix_equal(c, read_matrix("sub.matrix"))) {
		printf("sub test failed!\n");
		return false;
	}

	c = matrix_mult(a, b);
	if (!matrix_equal(c, read_matrix("mult.matrix"))) {
		printf("mult test failed!\n");
		return false;
	}
	return true;
}


int main() {
	if test() {
		printf("All test passed.\n");
	}
	return 0;
}
