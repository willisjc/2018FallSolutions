/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw15.h"

#ifdef LINKEDLIST
// Do not modify this function.
void LinkedListPrint(Node *head)
{

	Node *temp = head;

	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			printf("%d,", temp->value);
		}
		else
		{
			printf("%d\n", temp->value);
		}
		temp = temp->next;
	}
}
#endif

/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_CREATENODE

Node *CreateNode(int val)
{
	/*
	Create a new Node with `value` set to `val`. Set `next` to NULL.
	*/
	Node *node = malloc(sizeof(Node));
	node->value = val;
	node->next = NULL;
	return node;
}
#endif

#ifdef TEST_LINKEDLISTCREATE

void LinkedListCreate(Node **head, char *name)
{
	/*
	Create a linked list from the input file referenced by `name`.
	*/
	FILE *fptr = fopen(name, "r");
	int x = 0;
	int count = 0;
	while (fscanf(fptr, "%d", &x) != EOF)
	{
		count++;
	}
	// allocate memory to store the numbers
	int *arr = malloc(sizeof(int) * count);
	if (!arr)
	{
		fprintf(stderr, "failed to malloc for int array");
		return;
	}
	// use fscanf to read the file for its contents.
	fseek(fptr, 0, SEEK_SET);
	int i;
	for (i = 0; i < count; i++)
	{
		fscanf(fptr, "%d", &arr[i]);
	}
	fclose(fptr);
	if (count < 0)
	{
		return;
	}
	Node *node = CreateNode(arr[0]);
	*head = node;
	for (i = 1; i < count; i++)
	{
		node->next = CreateNode(arr[i]);
		node = node->next;
	}
	free(arr);
}
#endif
#ifdef TEST_REMOVED
//This function will remove repetitions of a linked list value.

void RemoveDuplicate(Node *headRef)
{
	/*
	This function will remove repetitions from the linked list referenced by headRef.
	Each time we check for a new Node in the linked list, we will check if it is distinct from
	the Nodes already present in the list ( upto the previous Node).
	So for each occurrence after its first, we will be deleting that node.
	To delete a node: we will map the next Node of the previous Node to the Node after the current Node.
	Print the linked list after all repetitions have been removed. Use the function given to you for priniting.
	*/
	Node *node = headRef;
	Node *check = NULL;
	int rel;
	while (node->next)
	{
		check = headRef;
		rel = 1;
		while (check != (node->next))
		{
			if (check->value == node->next->value)
			{
				Node *temp = node->next;
				node->next = node->next->next;
				free(temp);
				rel = 0;
			}
			check = rel?check->next:node->next;
		}
		if (rel)
		{
			node = node->next;
		}
	}

	LinkedListPrint(headRef);
}
#endif
