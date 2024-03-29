#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

//***** YOU NEED TO MODIFY main() FUNCTION BELOW *******//
#ifdef TEST_MAIN
void _FreeTree(treeNode * node) {
        if (node) {
                _FreeTree(node->leftChild);
                _FreeTree(node->rightChild);
                free(node);
        }
}
int main(int argc, char **argv)
{

	/*
	 *  1. Check for number of arguments. If less than 2, do not proceed further.
	 *
	 *  2. The program should create a binary search tree from the numbers in input file. The input file 
	 *  	also contains a number for search query at the end. 
	 *
	 *  3. The input file has one number per line. If there are 'n' lines in the file, the first n-1 numbers 
	 *  	are the elements of the binary search tree and the nth line is the search query. 
	 *  	NOTE: n is not given to you. 
	 *
	 *  4. Create an array of the first n-1 numbers and store the last number in a variable.
	 *
	 *  5. Create a Binary Search Tree. It takes four arguments:
	 *  	1. The array
	 *  	2. the first element of the array
	 *  	3. start index (index of first element of the array)
	 *  	4. end index ( index of last element of the array)
	 *
	 *  6. Print the created tree in Inorder fashion. Quick check if you have created the tree right: the output of
	 *  	will be a sorted array of numbers. 
	 *
	 *  7. Compute the distance of the 'search query' node by passing it to the function.
	 *
	 *  8. Use PrintDistance() function to print the distance of the node from the root node in the right format.
	 *
	 *  9. Free all memory.
	 *
	 */
	if (argc < 2)
	{
		return EXIT_FAILURE;
	}
	FILE *fptr = fopen(argv[1], "r");
	int n = 0;
	int x;
	for (x = fgetc(fptr); x != EOF; x = fgetc(fptr))
	{
		if (x == '\n')
		{
			n++;
		}
	}
	fseek(fptr, 0, SEEK_SET);
	int *a = malloc(sizeof(int) * n - 1);
	int i;
	for (i = 0; i < n - 1; i++)
	{
		fscanf(fptr, "%d", &a[i]);
	}
	int search_query;
	fscanf(fptr, "%d", &search_query);
	fclose(fptr);
	treeNode *node = CreateBST(a, a[0], 0, n - 2);
	BinaryTreeInOrderPrint(node);
	int dist = FindDistance(node, search_query, 0);
	PrintDistance(dist);
	free(a);
	_FreeTree(node);
}
#endif
