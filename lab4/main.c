#include "main.h"


int main() {
	int x, res, i;

	list l = list_read();
	printf("Read list: ");
	print_list(l);

	printf("Add (0, 1) to the back: \n");
	list_add_back(l, 0, 1);
	print_list(l);
}
