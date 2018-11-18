//edit this file as required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw18.h"

//Do Not Change this function
void PrintAnswer(ListNode *head, ListNode *min1, ListNode *min2)
{
	ListNode *temp = head;
	int i;
	while (temp != NULL)
	{
		i = 0;
		while (i < head->treenode->dimension)
		{
			if (i == 0)
				printf("(%d, ", temp->treenode->data[i]);
			else if (i == head->treenode->dimension - 1)
				printf("%d)\n", temp->treenode->data[i]);
			else
				printf("%d, ", temp->treenode->data[i]);
			i += 1;
		}
		temp = temp->next;
	}

	i = 0;
	while (i < head->treenode->dimension)
	{
		if (i == 0)
			printf("(%d, ", min1->treenode->data[i]);
		else if (i == head->treenode->dimension - 1)
			printf("%d) <-> ", min1->treenode->data[i]);
		else
			printf("%d, ", min1->treenode->data[i]);
		i += 1;
	}

	i = 0;
	while (i < head->treenode->dimension)
	{
		if (i == 0)
			printf("(%d, ", min2->treenode->data[i]);
		else if (i == head->treenode->dimension - 1)
			printf("%d)\n", min2->treenode->data[i]);
		else
			printf("%d, ", min2->treenode->data[i]);
		i += 1;
	}
}

/*
YOU CAN EDIT BELOW THIS COMMENT
*/

#ifdef TEST_MIN
void FindMin(ListNode *head)
{
	// find pair of ListNodes with least distance between them.
	if (!head)
	{
		fprintf(stderr, "FindMin called with NULL head");
		return;
	}
	if (!head->next)
	{
		fprintf(stderr, "FindMin called with length 1 LinkedList");
		return;
	}
	ListNode *node1 = head;
	ListNode *node2;
	ListNode *min1;
	ListNode *min2;
	int mindist;
	int dist;
	int x = 1;
	do
	{
		node2 = node1->next;
		while (node2)
		{
			dist = FindDist(node1->treenode, node2->treenode);
			if (x)
			{
				mindist = dist;
				min1 = node1;
				min2 = node2;
				x = 0;
			}
			if (dist < mindist)
			{
				mindist = dist;
				min1 = node1;
				min2 = node2;
			}
			node2 = node2->next;
		}
		node1 = node1->next;
	} while (node1);

	// call print Function
	/*
	ENSURE the 2nd parameter of the print function (min1) is smaller than
	the 3rd parameter (min2). 
	Look at README, and expected output for more details.
	*/
	int * arr1 = (min1->treenode)->data;
	int * arr2 = (min2->treenode)->data;
	int i = 0;
	while (i < min1->treenode->dimension && arr1[i] == arr2[i]) {
		i++;
	}
	if (arr1[i] - arr2[i] > 0)
	{
		node2 = min2;
		min2 = min1;
		min1 = node2;
	}
	PrintAnswer(head, min1, min2);
}
#endif

#ifdef TEST_DIST
int FindDist(TreeNode *x, TreeNode *y)
{
	//find the eucledian distance between
	// x->data and y->data
	// DO NOT FIND SQUARE ROOT (we are working with int)
	// return the distance
	if (x->dimension != y->dimension)
	{
		fprintf(stderr, "FindDist called between nodes of different dimensions");
		return EXIT_FAILURE;
	}
	int sum = 0;
	int i;
	int dif;
	for (i = 0; i < x->dimension; i++)
	{
		dif = y->data[i] - x->data[i];
		sum += dif * dif;
	}
	return sum;
}
#endif

#ifdef TEST_CREATENODE
ListNode *CreateNode(int n, int dim, int *arr)
{
	ListNode *listNode = malloc(sizeof(ListNode));
	if (!listNode)
	{
		fprintf(stderr, "ListNode malloc fail");
		return NULL;
	}
	// check for malloc error
	listNode->treenode = malloc(sizeof(TreeNode));
	listNode->next = NULL;
	TreeNode *tree = listNode->treenode;
	// initialize dim
	tree->dimension = dim;
	// both left and right childern will be NULL
	tree->left = NULL;
	tree->right = NULL;
	// allocate memory for data
	tree->data = malloc(sizeof(int) * dim);
	int i;
	for (i = 0; i < dim; i++)
	{
		tree->data[i] = arr[i];
	}
	// return a ListNode
	return listNode;
}
#endif

#ifdef TEST_LINKEDLISTCREATE
void LinkedListCreate(ListNode **head, int n, int dim, FILE *fptr)
{
	// create temp node using CreateNode
	// read from file into an array, pass array to CreateNode
	// assign temp to that node
	int i;
	int *arr = malloc(sizeof(int) * dim);
	for (i = 0; i < dim; i++)
	{
		fscanf(fptr, "%d", &arr[i]);
	}
	ListNode *tempNode = CreateNode(n, dim, arr);
	*head = tempNode;
	// use a loop to create nodes for the remaining elements of the list.
	int j;
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < dim; j++)
		{
			fscanf(fptr, "%d", &arr[j]);
		}
		tempNode->next = CreateNode(n, dim, arr);
		tempNode = tempNode->next;
	}
	free(arr);
}
#endif
