#include "main.h"


int main() {
	int x, res, i, find_key=2;
	size_t list_len_ = 0;
	node* node_ = NULL;

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
	printf("list's length = %lu\n", list_len(l));

	printf("list's sum    = %d\n", list_sum(l));

	node_ = list_node_at(l, 4);
	printf("list's 4th item = (%4d; %4d)\n", node_->key, node_->value);

	list_free(l);
}
