#include "main.h"


int main() {
	void* init = init_heap(50);
	if (init == NULL) {
		printf("can not initialize heap.\n");
	}

	int* i = memalloc(sizeof(int));
	float* j = memalloc(sizeof(float));
	*i = 12;
	*j = 12.9;
	printf("%d\n", *i);
	printf("%f\n", *j);
	memfree(i);
	memfree(j);
}
