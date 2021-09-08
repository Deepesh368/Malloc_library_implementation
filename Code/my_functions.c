#include "my_functions.h"

void *my_heap_ptr;
size_t memory_size;

struct memory_block {  /*The structure of the header for each memory block. It contains information about the size of memory block allocated and its occupied state.*/
	
	size_t block_size; /* The size of the memory block that this header is pointing to.*/
	
	int occupied;   /* If 'occupied' is 1 then the block is already allocated and cannot be used.*/
	
	struct memory_block *next; /*This makes a linked list so that all of the memory blocks are connected and traversal is possible.*/
};

struct memory_block *start; /*pointer to start of memory which is initially free which will be used to reference the start of the main memory header*/

void initialise_memory() /*Initially the memory does have any header. We create a header for the memory with this function.*/
{
	start -> block_size = (memory_size) - sizeof(struct memory_block); /* Once we create a header we subtract the size of the header from the total size.*/
	start -> occupied = 0;
	start -> next = NULL;
	printf("Memory initialised\n");
}

void split_memory(struct memory_block* required, size_t size) /*Function to split a memory block whose size is larger than the required size.*/
{
	struct memory_block *new_block = (void*)((void*)required + size + sizeof(struct memory_block));
	new_block -> block_size = (required -> block_size) - size - sizeof(struct memory_block);
	new_block -> occupied = 0;
	new_block -> next = required -> next;  
	required -> block_size = size;
	required -> occupied = 1;
	required -> next = new_block;
}

void merge_memory()  /*Function to merege adjacent memory blocks which are both free so that space is conserved.*/
{
	struct memory_block *previous_block, *current_block;
	current_block = start;
	while(current_block -> next != NULL)
	{
		if((current_block -> occupied == 0) && (current_block -> next -> occupied == 0)) /* If we find two consecutive memory blocks which not allocated then we merge them.*/
		{
			current_block -> block_size = current_block -> block_size + current_block -> next -> block_size + sizeof(struct memory_block);
			current_block -> next = current_block -> next -> next;
		}
		previous_block = current_block;
		current_block = current_block -> next;
	}
}

void* my_malloc(size_t size)  /*My malloc implementation.*/
{
	void *return_pointer;
	struct memory_block *previous_block, *current_block;
	current_block = start;
	while((current_block -> block_size < size || current_block -> occupied == 1) && (current_block -> next != NULL))
	{
		previous_block = current_block;
		current_block = current_block -> next;
		printf("Passed over a undesirable block of memory\n");
	}
	if(current_block -> occupied == 0 && current_block -> block_size == size)
	{
		current_block -> occupied = 1;
		current_block++;
		return_pointer = (void*)current_block;
		printf("Block whose size is exactly what we need is found\n");
		return return_pointer;
	}
	else if(current_block -> occupied == 0 && current_block -> block_size > size + sizeof(struct memory_block))
	{
		split_memory(current_block, size);
		current_block++;
		return_pointer = (void*)current_block;
		printf("Block whose size is more than what we need is found\n");
		return return_pointer;
	}
	else
	{
		printf("Could not find a suitable block\n");
		return NULL;
	}
}

void my_free(void* ptr) /*My 'free' function implementation.*/
{
	if(ptr != NULL)
	{
		struct memory_block *current_block = ptr;
		current_block--;
		current_block -> occupied = 0;
		merge_memory(); 
	}
}

void* my_calloc(size_t nmemb, size_t size) /*My calloc function implementation.*/
{
	void* pointer = my_malloc(nmemb * size);
	memset(pointer, '\0', nmemb * size);
	return pointer;
}

size_t my_heap_free_space(void) /*My implementation of my_heap_free_space function.*/
{
	size_t result = 0;
	struct memory_block *current_block;
	current_block = start;
	while(current_block != NULL)
	{
		if(current_block -> occupied == 0)
		{
			result += current_block -> block_size;
		}
		current_block = current_block -> next;
	}
	return result;
}
