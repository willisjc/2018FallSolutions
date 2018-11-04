/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw14.h"


/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_CREATENODE

Node * CreateNode(int val)
//val: value of the element of the node to be created
{
	// same as previous homeworks
  Node * newNode = malloc(sizeof(Node));
  if (!newNode) {
    fprintf(stderr, "Node memory allocation fail");
    return NULL;
  }
  newNode->value = val;
  newNode->next = NULL;
  return newNode;
}
#endif

#ifdef TEST_LINKEDLISTCREATE
//source: the head of the singly linkedlist.
//len: the length of the array.
//arr: the array with the contents of the input file.

void LinkedListCreate(Node * * source, int len, int* arr)
{
	// Refer HW13 and HW12
	// Tip: use CreateNode(arr[index])
  if (len < 0) {
    return;
  }
  Node * node = *source;
  int i;
  for (i = 1; i < len; i++) {
    node->next = CreateNode(arr[i]);
    node = node->next;
  }
}

#endif


#ifdef TEST_SPLIT
// source is the head of the list to be split.
// head1 is the head of the upper sub-list.
// head2 is the head of the lower sub-list.

void SplitList(Node* source, Node** head1, Node** head2)
{
	// Refer HW13
  Node * node = source;
  *head1 = source;
  int length = 0;
  do {
    node = node->next;
    length++;
  } while (node);
  node = source;
  int mid = (length + 1) / 2;
  int elem;
  //123 45
  //12 34
  for (elem = 1; elem < mid; elem++) {
    node = node->next;
  }
  *head2 = node->next;
  node->next = NULL;
} 
#endif

#ifdef TEST_MERGE
// upper is the upper sub-list to be merged
// lower is the lower sub-list to be merged
Node* Merge(Node* upper, Node* lower) 
{ 
  // Check for the base cases. (When either sub-list is NULL)
  if (!upper || !lower) {
    if (upper) {
      return upper;
    }
    if (lower) {
      return lower;
    }
    return NULL;
  }
  // Pick the larger between upper and lower, and recur appropriately.
  if (upper->value >= lower->value) {
    lower->next = Merge(upper, lower->next);
    return lower;
  }
  else {
    upper->next = Merge(upper->next, lower);
    return upper;
  }
  // return the merged array
} 
#endif

#ifdef TEST_SORT
// source is the head of the list to for which MergeSort is to be performed.
void MergeSort(Node** source) 
{ 
  // Declare a node, to hold the current head of the source list.
  Node * node = *source;
  // Declare nodes, to hold the two the heads of the two sub-lists.
  Node * node1 = NULL;
  Node * node2 = NULL;
  Node ** head1 = &node1;
  Node ** head2 = &node2;
  // Check for the base case -- length 0 or 1
  // if so, return;
  if (!node || !node->next) {
    return;
  }
  // Use SpiltList() to partition the list into sub lists.
  // This will partiton the source list, into two lists (As done in the previous homework)
  SplitList(node, head1, head2);
  // Recursively sort the sub-lists by calling MergeSort() on the upper and lower sub-lists.
  MergeSort(head1);
  MergeSort(head2);
  // MergeSort() is a recursive function, and MergeSort() needs to be called
  // on both sub-lists (obtained after partitioning)
  node = Merge(*head1, *head2);
  // Merge the two sorted lists together, using the Merge()
}
void LinkedListFree(Node * * head) {
  Node * node = *head;
  do {
    Node * kharon = node;
    node = node->next;
    free(kharon);
  } while (node);
}
#endif

