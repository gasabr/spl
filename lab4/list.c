#include "list.h"


node* allocate_node(int key, int value, node* next) {
	node* new_node = malloc(sizeof(node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = next;

	return new_node;
}


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
		t_node = allocate_node(read_key, 1 << read_key, root);
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


void list_add_back(list* lst, int key, int value) {
	// adds node to the back of the list
	node* t_node = *lst;
	node* new_node = allocate_node(key, value, NULL);

	if (t_node == NULL) {
		lst = new_node;
		return;
	}

	while (t_node->next != NULL) {
		t_node = t_node->next;
	}

	t_node->next = new_node;
	return;
}


void list_add_front(list* lst, int key, int value) {
	node* current_root = *lst;
	*lst = allocate_node(key, value, current_root);

	return;
}

int get(list lst, const int key) {
	node* current_node = lst;
	while (current_node->key != key && current_node != NULL) {
		current_node = current_node->next;
	}

	if (current_node == NULL) {
		return 0;
	}
	else {
		return current_node->value;
	}
}
