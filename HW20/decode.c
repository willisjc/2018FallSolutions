// Modify this file at said locations
#include "decode.h"
#include "list.h"
#include "utility.h"

/*
------------------------------------------------------------------------------
You Can Modify below, Do Not modify above this
------------------------------------------------------------------------------
*/

#ifdef TEST_READHEADER

TreeNode *readHeader(FILE *infptr)
{
	/* This function should have the following logic
	 * The first bit is a command bit and it is always 1.
	 * If a command is 1, then the next 8 bits(for this assignment) are the value stored
	 	 in a leaf node. Create a tree node to store this value. Add this tree node to the
		 beginning of the linked list (basically, LinkedList is acting like a stack here).
     This tree node is a single-node tree.  
	 * If a command is 0 and the list has two or more nodes, then take the first two nodes from
	 	 the list, create a tree node as the parent. Add this parent node to the linked list.
   * If a command is 0 and the list has only one node, then the complete tree has been built.
	 * After the tree is completely built, then read one more bit. If this is not the last
	 	 (rightmost) bit of the byte, discard the remaining bits in the byte.
	*/

	int n;
	int nodes = 0;
	unsigned char bit;
	unsigned char whichbit;
	unsigned char curbyte;
	unsigned char val;
	ListNode *head = NULL;
	while (1)
	{
		readBit(infptr, &bit, &whichbit, &curbyte);
		if (bit) {
			readBit(infptr, &bit, &whichbit, &curbyte);
			val = bit;
			for (n = 0; n < 7; n++) {
				val = val << 1;
				readBit(infptr, &bit, &whichbit, &curbyte);
				val += bit;
			}
			head = List_insert(head, ListNode_create(TreeNode_create(val, 0)));
			nodes++;
		}
		else if (nodes > 1) {
			MergeListNode(head);
			nodes--;
		}
		else {
			
			TreeNode * tn = head->tnptr;
			free(head);
			return tn;
			
		}
		
	}
	return NULL;
}

#endif

#ifdef TEST_DECODE

int decode(char *infile, char *outfile)
{
	// read the header from the input file  by calling readHeader function
	FILE *infptr = fopen(infile, "rb");
	if (!infptr)
	{
		fprintf(stderr, "failed to open infile");
		return -1;
	}
	TreeNode *tn = readHeader(infptr);
	// the generated tree from the header generated should be printed in outfile
	// to print the tree into the file use Tree_print function given to you.
	FILE *outfptr = fopen(outfile, "wb");
	if (!outfptr)
	{
		fprintf(stderr, "failed to open outfile");
	}
	Tree_print(tn, outfptr);
	// After reading the header till codebook, read the next 4 bytes from the header,
	// these 4 bytes represent number of characters in the file.
	unsigned int num;
	fread(&num, sizeof(unsigned int), 1, infptr);
	// Print the number of characters obtained by using the PrintNumberChar function
	// Do not use your own print functions
	PrintNumberChar(num, outfptr);
	// free up the memory
	Tree_destroy(tn);
	fclose(infptr);
	fclose(outfptr);
	return 1;
}
#endif
