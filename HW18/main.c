// Edit this file as required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw18.h"

#ifdef TEST_MAIN
int main(int argc, char **argv)
{
	// check for input error
	if (argc != 2)
	{
		return EXIT_FAILURE;
	}
	// open the file
	FILE *fptr = fopen(argv[1], "r");
	// input file is in argv[1]

	// n is the element in the file
	int n;
	fscanf(fptr, "%d", &n);
	// dim is the second element in the file
	int dim;
	fscanf(fptr, "%d", &dim);
	// the rest of the data in the file are the datapoints.

	// call LinkedListCreate
	ListNode **head = malloc(sizeof(ListNode *));
	LinkedListCreate(head, n, dim, fptr);
	ListNode *node = *head;
	fclose(fptr);
	// call FindMin
	FindMin(node);
	while (node != NULL)
	{
		free((node->treenode)->data);
		free(node->treenode);
		ListNode * charon = node;
		node = node->next;
		free(charon);
	}
	free(head);
}
#endif
