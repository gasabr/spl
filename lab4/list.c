#include "list.h"


list list_create(int key, int value) {
	list root;
	root->key = key;
	root->value = value;
	root->next = NULL;

	return root;
}


list list_read() {
	// reads list from stdin
	list root = NULL;
	list t_node = NULL;
	int read_key;

	while (fscanf(stdin, "%d", &read_key) != 0) {
		if (feof(stdin)) {
			break;
		}
		t_node = malloc(sizeof(node));

		t_node->key = read_key;
		t_node->value = 1 << read_key;
		t_node->next = root;

		root = t_node;
	}
	
	return root;
}


void print_list(list const lst) {
	list next = lst;

	if (next == NULL) {
		return;
	}

	while (next->next != NULL) {
		printf("(%4d; %4d) -> ", next->key, next->value);
		next = next->next;
	}
	printf("(%4d; %4d)\n", next->key, next->value);
	return;
}


/* int list_add_back(list* const lst, node* new_node) { */
/*     node *t_node = lst->root; */
/*     int x; */

/*     if (lst->len == 0) { */
/*         printf("len 0 case\n"); */
/*         lst->root = new_node; */
/*         lst->len = 1; */
/*     } else { */
/*         [> t_node = lst->root; <] */
/*         printf("inside = %lu\n", lst->root->next); */
/*         [> while (t_node->next != NULL) { <] */
/*         [>     t_node = t_node->next; <] */
/*         [>     printf("%lu\n", t_node); <] */
/*         [>     scanf("%d", &x); <] */
/*         [> } <] */
/*     } */
/*     t_node->next = new_node; */
/*     printf("t_node.key = %d\n", t_node->key); */
/*     lst->len += 1; */
	
/*     return lst->len; */
/* } */


/* int list_add_front(list* lst, node new_node) { */
/*     return 0; */
/* } */
