/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw14.h"


#ifdef LINKEDLIST
// Do not modify this function, we are using this within ifdef block for
// ease of grading.
void LinkedListPrint(Node * * source)
{

	Node *temp = * source;

	while(temp!=NULL)
	{
		if(temp->next!=NULL)
		{
			printf("%d,",temp->value);
		}
		else
		{
			printf("%d",temp->value);
		}
		temp=temp->next;
	}
	printf("\n");
}
#endif

/****************** DO NOT Modify this file above this line *************************/

// Modify the following function
#ifdef TEST_MAIN
void LinkedListFree(Node * * head);
int main(int argc, char **argv)
{
  // if argc is less than 2 then, return EXIT_FAILURE
  // input file is specified through the Makefile.
  if (argc < 2) {
    fprintf(stderr, "not enough arguments");
    return EXIT_FAILURE;
  }
  // open file to read
  FILE * fptr = fopen(argv[1], "r");
  // check for fopen fail. If so, return EXIT_FAILURE
  if (!fptr) {
    fprintf(stderr, "failed to open file");
    return EXIT_FAILURE;
  }
  // count the number of integers in the file.
  int x = 0;
  int count = 0;
  while (fscanf(fptr, "%d", &x) != EOF) {
    count++;    
  }
  // allocate memory to store the numbers
  int * arr = malloc(sizeof(int) * count);
  // check for malloc fail, if so, return EXIT_FAILURE
  if (!arr) {
    fprintf(stderr, "failed to malloc for int array");
    return EXIT_FAILURE;
  }
  // use fscanf to read the file for its contents.
  fseek(fptr, 0, SEEK_SET);
  int i;
  for (i = 0; i < count; i++) {
    fscanf(fptr, "%d", &arr[i]);
  }
  fclose(fptr);
  // create head node, which corresponds to the head of the linked-list.
  Node * node = CreateNode(arr[0]);
  Node ** head = &node;
  // You must now use the appropriate function to construct the remaining list.
  LinkedListCreate(head, count, arr);
  free(arr);
  // call MergerSort() function for final output.
  MergeSort(head);
  // This will call a recursive function.
  // The input list will be divided into two sub-lists recursively,
  // Then the contents of the sub-lists are compared and merged back to form the
  // sorted output list.
  
  // use the provided function to print the final list.
  LinkedListPrint(head);
  // Tip: Check for memory errors.
  LinkedListFree(head);
  return EXIT_SUCCESS;
}

#endif
