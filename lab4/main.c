#include "main.h"


int main() {
	int x, res, i;
	list l = list_create(1, 2);
	printf("outside = %lu\n", l.root->next);

	node current_node;
	node *p_node;
	while (fscanf(stdin, "%d", &x) != NULL) {
		if (feof(stdin)) {
			break;
		}
		current_node.key = x;
		current_node.value = 2 << x;
		current_node.next = NULL;

		/* printf("debug point\n"); */
		res = list_add_back(&l, &current_node);
		printf("outside2 = %lu\n", l.root->next);
	}

	printf("add_back works now\n");
	p_node = l.root;
	while (p_node != NULL) {
		printf("(%4d; %4d) -> ", p_node->key, p_node->value);
		p_node = p_node->next;
	}
}
