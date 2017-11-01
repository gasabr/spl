#include <stddef.h>
#include <stdio.h>


typedef struct Node {
	int key;
	int value;
	struct Node* next;
} node;


typedef node* list;

// initialisation of the list
list list_create(int key, int value);
list list_read();

void print_list(list const);

// adding elements
int list_add_back(list const lst, list new_node);
int list_add_front(list const lst, const node new_node);
