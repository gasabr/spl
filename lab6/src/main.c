#include "main.h"


int main() {
	void* init = init_heap(50);
	if (init == NULL) {
		printf("can not initialize heap.\n");
	}

	int* i = memalloc(sizeof(int));
	float* j = memalloc(sizeof(float));

	*i = 12;
	*j = 128;

	FILE* log = fopen("log", "wa+");
	memalloc_debug_heap(log, init);

	printf("%zu %d\n", (size_t)i, *i);
	printf("%zu %f\n", (size_t)j, *j);

	/* fclose(log); */
	memfree(j);
	memfree(i);
}
