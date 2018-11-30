// Please modify this file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw19.h"


#ifdef TEST_MAIN
void _TreeFree(TreeNode * tn) {
	if (!tn) {
		return;
	}
	_TreeFree(tn->left);
	_TreeFree(tn->right);
	free(tn->data);
	free(tn);
}
int main(int argc, char * * argv)
{
	// check for input error
	if (argc != 2) {
		fprintf(stderr, "wrong arguments");
		return EXIT_FAILURE;
	}
	// open the file
	FILE * fptr = fopen(argv[1], "r+");
	if (!fptr) {
		fprintf(stderr, "failed to open file");
		return EXIT_FAILURE;
	}
	int n;
	fscanf(fptr, "%d", &n);
	int dim;
	fscanf(fptr, "%d", &dim);
	ListNode ** head = malloc(sizeof(ListNode * ));
	// Create linkedList
	LinkedListCreate(head, n, dim, fptr);
	fclose(fptr);
	// call MakeCluster
	MakeCluster(head);
	ListNode * node = *head;
	while (node != NULL)
	{
		_TreeFree(node->treenode);
		ListNode * charon = node;
		node = node->next;
		free(charon);
	}
	free(head);
	return EXIT_SUCCESS;
}
#endif
