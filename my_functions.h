#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern void *my_heap_ptr; /*This is the pointer pointing to the start of the memory which will serve as our main memory for malloc.*/
extern size_t memory_size;
extern struct memory_block *start;

void initialise_memory();
void split_memory(struct memory_block* required, size_t size);
void merge_memory();
void* my_malloc(size_t size);
void my_free(void* ptr);
void* my_calloc(size_t nmemb, size_t size);
size_t my_heap_free_space(void);
