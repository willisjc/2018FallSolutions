// You can modify this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw19.h"

// DO NOT MODIFY THIS FUNCTION
void PrintAns(ListNode *head, ListNode *min1, ListNode *min2)
{
	int i;
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
MODIFY BELOW THIS COMMENT
*/

#ifdef TEST_CENT
ListNode *FindCentroid(TreeNode *x, TreeNode *y)
{
	//create new listnode
	ListNode *new = malloc(sizeof(ListNode));
	if (!new)
	{
		fprintf(stderr, "malloc fail for ListNode in FindCentroid");
		return NULL;
	}
	//listnode->next
	new->next = NULL;
	//listnode->treenode
	new->treenode = malloc(sizeof(TreeNode));
	if (!new->treenode)
	{
		free(new);
		fprintf(stderr, "malloc fail for treenode in FindCentroid");
		return NULL;
	}
	//listnode->treenode->data
	(new->treenode)->data = malloc(sizeof(int) * (x->dimension));
	if (!new->treenode)
	{
		free(new->treenode);
		free(new);
		fprintf(stderr, "malloc fail for data in FindCentroid");
		return NULL;
	}
	//listnode->treenode->dimension
	(new->treenode)->dimension = x->dimension;
	//listnode->treenode->data = (x+y)/2
	int xsum = 0;
	int ysum = 0;
	int i;
	for (i = 0; i < x->dimension; i++)
	{
		xsum += (x->data[i] * x->data[i]);
		ysum += (y->data[i] * y->data[i]);
		(new->treenode)->data[i] = (x->data[i] + y->data[i]) / 2;
	}
	//min(x,y) = left, max=right
	if (xsum < ysum)
	{
		(new->treenode)->left = x;
		(new->treenode)->right = y;
	}
	else
	{
		(new->treenode)->left = y;
		(new->treenode)->right = x;
	}
	//return node
	return new;
}
#endif

#ifdef TEST_DIST
int FindDist(TreeNode *x, TreeNode *y)
{
	if (x->dimension != y->dimension)
	{
		fprintf(stderr, "FindDist called between nodes of different dimensions");
		return -1;
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

#ifdef TEST_FUSE
ListNode *Fuse(ListNode *head, ListNode *fuse1, ListNode *fuse2)
{
	// Create a new ListNode element using findCentroid function.
	ListNode *listNode = FindCentroid(fuse1->treenode, fuse2->treenode);
	// The new->treenode.data will hold the averaged values of the two parameters' data (fuse1, and fuse2)
	// add the new ListNode to the list.
	listNode->next = fuse1->next;
	ListNode *node = fuse1 == head ? listNode : head;
	while (node)
	{
		if (node->next == fuse1)
		{
			node->next = listNode;
		}
		if (node->next == fuse2)
		{
			node->next = (node->next)->next;
		}
		node = node->next;
	}
	return fuse1 == head ? listNode : head;
	// remove the fuse1 and fuse2 from the list. (Do NOT free)
	// you may want to return head from this function (depending on your implementation)
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

#ifdef TEST_CLUSTER
void MakeCluster(ListNode **head)
{
	// Walk through the linked list.
	// find pair of nodes with minimum distance.
	// fuse the two nodes into one node.
	// call print function
	// repeat till one node is remaining.
	ListNode *node1 = NULL;
	ListNode *node2 = NULL;
	ListNode *min1 = NULL;
	ListNode *min2 = NULL;
	int mindist;
	int dist;
	int i;
	while ((*head)->next)
	{
		node1 = *head;
		//find closest nodes
		while (node1)
		{
			node2 = node1->next;
			while (node2)
			{
				dist = FindDist(node1->treenode, node2->treenode);
				if (!min1 || !min2)
				{
					mindist = dist;
					min1 = node1;
					min2 = node2;
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
		}
		*head = Fuse(*head, min1, min2);
		
		i = 0;
		while (min1->treenode->data[i] == min2->treenode->data[i]) {
			i++;
		}
		if (min1->treenode->data[i] > min2->treenode->data[i]) {
			PrintAns(*head,min2,min1);
		}
		else {
			PrintAns(*head,min1,min2);
		}
		//min(x,y) = left, max=right
		
		ListNode *charon = min1;
		min1 = NULL;
		free(charon);
		ListNode *charon1 = min2;
		min2 = NULL;
		free(charon1);
	}
}
#endif
