#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>		// malloc


typedef struct Node {
	int key;
	int value;
	struct Node* next;
} node;


typedef node* list;

node* allocate_node(int key, int value, node* next);

// initialisation of the list
list list_create(int key, int value);
list list_read();

void print_list(list const);

// adding elements
void list_add_back(list* lst, int key, int value);
void list_add_front(list* lst, int key, int value);

int get(list lst, int key);

void list_free(list lst);

size_t list_len(list lst);
