#include "list.h"


list list_create(int key, int value) {
	list created_list;
	node root;
	root.key = key;
	root.value = value;
	root.next = NULL;

	created_list.root = &root;
	created_list.len = 1;

	return created_list;
}


void print_list(list* const lst) {
	node* current_node = lst->root;

	if (current_node == NULL) {
		return;
	}
	printf("node.key = %d\n", current_node->key);

	while (current_node != NULL) {
		printf("(%4d; %4d) -> ", current_node->key, current_node->value);
		current_node = current_node->next;
	}
	/* printf("(%4d; %4d) -> ", current_node->key, current_node->value); */
	return;
}


int list_add_back(list* const lst, node* new_node) {
	node *t_node = lst->root;
	int x;

	if (lst->len == 0) {
		printf("len 0 case\n");
		lst->root = new_node;
		lst->len = 1;
	} else {
		/* t_node = lst->root; */
		printf("inside = %lu\n", lst->root->next);
		/* while (t_node->next != NULL) { */
		/*     t_node = t_node->next; */
		/*     printf("%lu\n", t_node); */
		/*     scanf("%d", &x); */
		/* } */
	}
	t_node->next = new_node;
	printf("t_node.key = %d\n", t_node->key);
	lst->len += 1;
	
	return lst->len;
}


int list_add_front(list* lst, node new_node) {
	return 0;
}
