/* This program contains my implementation of some functions in the malloc library.
   All of the functions and the algorithms I have used in this program will be explained in more detail in the design
   document.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "my_functions.h"

int main(void)
{
	memory_size = 80000; /* The total size of the memory we can use. */
	my_heap_ptr = (void*)malloc(memory_size); /* We now use 'malloc' to create a memory of 80000 bytes which will be the main memory of our malloc function.*/
	
	start = (void*) my_heap_ptr; /* We also make 'start' point to the start of the memory.*/
	
	initialise_memory(); /* We initialise the memory so that we can start operations.*/
	
	/*Test case 1 */
	int *array, i;
	array = (int*)my_malloc(10 * sizeof(int));
	for(i = 0;i < 10;i++)
	{
		array[i] = i+1;
	}
	printf("\n");
	printf("Test Case 1 Output Starts here\n");
	for(i = 0;i < 10;i++)
	{
		printf("%d,", array[i]);
	}
	printf("\n\n");
	
	/*Test Case 2 */
	char *letter;
	letter = (char*)my_malloc(10 * sizeof(char));
	for(i = 0;i < 10;i++)
	{
		letter[i] = 'a';
	}
	printf("\n\n");
	printf("Test Case 2 Output Starts here\n");
	for(i = 0;i < 10;i++)
	{
		printf("%c,", letter[i]);
	}
	printf("\n\n");
	
	/*Test Case 3 */
	int *array_c;
	array_c = (int*)my_calloc(10, sizeof(int));
	printf("\n\n");
	printf("Test Case 3 Output Starts here\n");
	for(i = 0;i < 10;i++)
	{
		printf("%d,", array_c[i]);
	}
	printf("\n\n");
	
	/* Test Case 4 */
	my_free(array);
	char *letter_f;
	letter_f = (char*)my_malloc(10 * sizeof(char));
	for(i = 0;i < 10;i++)
	{
		letter[i] = 'b';
	}
	printf("\n\n");
	printf("Test Case 4 Output Starts here\n");
	for(i = 0;i < 10;i++)
	{
		printf("%c", letter[i]);
	}
	printf("\n\n");
	return 0;
}
