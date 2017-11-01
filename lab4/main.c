#include "main.h"


int main() {
	int x, res, i, find_key=2;
	size_t list_len_ = 0;

	list l = list_read();
	printf("Read list: ");
	print_list(l);

	printf("Add (0, 1) to the back: \n");
	list_add_back(&l, 0, 1);
	print_list(l);

	printf("Add (6, 64) to the front: \n");
	list_add_front(&l, 6, 64);
	print_list(l);

	x = get(l, find_key);
	printf("list[%d] = %d\n", find_key, x);

	// WTF: it won't work with var named list_len
	list_len_ = list_len(l);
	printf("list's length = %lu\n", list_len_);

	list_free(l);
}
