#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

#define HEAP_START ((void*)0x04040000)
#define DEBUG_FIRST_BYTES 4
#define MIN_BLOCK_SIZE 8

#pragma pack(push, 1)
typedef struct mem {
	struct mem* next;
	size_t capacity;
	bool is_free;
} mem_t;
#pragma pack(pop)


void* init_heap(size_t);
void* memalloc(size_t n_bytes);
void memfree(void*);

mem_t* find_block(size_t);
mem_t* memmap(mem_t*, size_t);

#endif // MEM_H
