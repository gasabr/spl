#include <stddef.h>
#include <stdio.h>


typedef struct Node {
	int key;
	int value;
	struct Node* next;
} node;


typedef struct List {
	node* root;
	size_t len ;
} list;


void print_list(list* const);
list list_create(int key, int value);
int list_add_back(list* const lst, node* new_node);
int list_add_front(list* const lst, const node new_node);
