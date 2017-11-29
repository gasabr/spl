#include "mem.h"


/* static mem_t* FIRST_BLOCK = NULL; */
static mem_t* map;


void* memalloc(size_t query) {
	// check if there is a chunk with big enough to store requested n bytes

	mem_t* mem;
	mem_t* new_block;
	void* data_ptr = NULL;

	if (query < MIN_BLOCK_SIZE) {
		query = MIN_BLOCK_SIZE;
	}

	// try to find suitable block f memory for given n_bytes
	// (amoong existing ones)
	mem = find_block(query);

	// if there is no such block, try to map the new one
	if (mem == NULL) {
		// if there is no appropriate chunk, try to mmap the new one and link it
		// to the block chain :)
		printf("mem==NULL\n");
		mem_t* last_block = map;
		while (last_block->next != NULL) {
			last_block = last_block->next;
		}
		new_block = memmap(last_block, query + sizeof(mem_t));
		if (new_block == NULL) {
			return NULL;
		}

		last_block->next = new_block;
		printf("new last block addr = %zu\n", (size_t)last_block->next);
		data_ptr = (void*)((size_t)new_block + sizeof(mem_t));

		return data_ptr;

	} else {
		printf("mem!=NULL\n");
		// create new block after the found one
		if (mem->capacity > query + MIN_BLOCK_SIZE + sizeof(mem_t)) {
			new_block = (mem_t*) ((size_t)mem + sizeof(mem_t) + query);
			new_block->is_free = true;
			// link the next in the chain
			new_block->next = mem->next;
			new_block->capacity = mem->capacity - query - 2*sizeof(mem_t);
		} else {
			new_block = NULL;
		}

		mem->is_free  = false;
		mem->capacity = query;
		mem->next     = new_block;

		// skip the header and return pointer to the payload part of the page
		data_ptr = (void*)((size_t)mem + sizeof(mem_t));

		// return pointer to the data
		return data_ptr;
	}

	return NULL;
}


mem_t* find_block(size_t query) {
	// Finds block of allocated memory which can hold `query` bytes
	mem_t* current_block = map;

	while (current_block != NULL) {
		if (current_block->is_free	&& (query <= current_block->capacity)) {
			return current_block;
		}
		current_block = current_block->next;
	}
	return NULL;
}


mem_t* memmap(mem_t* last, size_t size) {
	long system_page_size = sysconf(_SC_PAGESIZE);
	mem_t* new_mapping;
	mem_t* mem = last;

	// pointer to the region next to allocated
	size_t end_address = ((size_t)mem + sizeof(mem_t) + mem->capacity);

	// calculate starting address for new mapping
	void* addr = (void*)(end_address + system_page_size
			- end_address % system_page_size);

	// try to map
	new_mapping = (mem_t*) mmap(addr, size, PROT_READ|PROT_WRITE,
			MAP_FIXED|MAP_SHARED|MAP_ANON, -1, 0);

	if (new_mapping == MAP_FAILED) {
		// if attempt to map memory right after already mapped fragments
		// was unsuccesful -- try to map somewhere
		new_mapping = (mem_t*) mmap(addr, size, PROT_READ|PROT_WRITE,
				MAP_SHARED|MAP_ANONYMOUS, -1, 0);
		// if this attempt failed -- return NULL
		if (new_mapping == MAP_FAILED)
			return NULL;
	}

	// here we can only have valid pointer in map
	new_mapping->next = NULL;
	new_mapping->is_free = true;
	new_mapping->capacity = size - sizeof(mem_t);

	return new_mapping;
}


void* init_heap(size_t init_size) {
	map = (mem_t*) mmap(HEAP_START, init_size + sizeof(mem_t),
			PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);

	if (map == MAP_FAILED){
		return NULL;
	}

	map->next = NULL;
	map->is_free = true;
	map->capacity = init_size;

	return map;
}


void memfree(void* to_be_freed) {
	printf("Enter ColeWorld\n");
	mem_t* block_to_be_freed = (mem_t*)((size_t)to_be_freed - sizeof(mem_t));
	mem_t* next_block = (mem_t*)((size_t)to_be_freed + block_to_be_freed->capacity);

	block_to_be_freed->is_free = true;

	if (next_block->is_free) {
		// merge two blocks
		// skip the next one
		block_to_be_freed->next = next_block->next;
		// increase current block's capacity
		block_to_be_freed->capacity += sizeof(mem_t) + next_block->capacity;
	}

	return;
}

// Debugging functions
void memalloc_debug_struct_info( FILE* f,
        mem_t const* const address ) {
	size_t i;
    fprintf( f,
            "start: %p\nsize: %lu\nis_free: %d\n",
            (void*)address,
            address-> capacity,
            address-> is_free );
    for ( i = 0; i < DEBUG_FIRST_BYTES  &&  i < address->capacity; ++i )
        fprintf( f, "%hhX",
                ((char*)address)[ sizeof( mem_t ) + i ] );
    putc( '\n', f );
}

void memalloc_debug_heap( FILE* f, mem_t const* ptr ) {
	fprintf(f, "--------------------\n");
    for( ; ptr; ptr = ptr->next )
		memalloc_debug_struct_info( f, ptr );
}
