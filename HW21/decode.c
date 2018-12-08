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
  // This is the same function from HW20
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
    if (bit)
    {
      readBit(infptr, &bit, &whichbit, &curbyte);
      val = bit;
      for (n = 0; n < 7; n++)
      {
        val = val << 1;
        readBit(infptr, &bit, &whichbit, &curbyte);
        val += bit;
      }
      head = List_insert(head, ListNode_create(TreeNode_create(val, 0)));
      nodes++;
    }
    else if (nodes > 1)
    {
      MergeListNode(head);
      nodes--;
    }
    else
    {
      TreeNode *tn = head->tnptr;
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
  // In this function, in addition to the last assignment, you will also decode the rest of the file.

  FILE *infptr = fopen(infile, "rb");
  if (!infptr)
  {
    fprintf(stderr, "failed to open infile");
    return -1;
  }
  TreeNode *head = readHeader(infptr);
  // the generated tree from the header generated should be printed in outfile
  // to print the tree into the file use Tree_print function given to you.
  FILE *outfptr = fopen(outfile, "w");
  if (!outfptr)
  {
    fprintf(stderr, "failed to open outfile");
  }
  Tree_print(head, outfptr);
  // After reading the header till codebook, read the next 4 bytes from the header,
  // these 4 bytes represent number of characters in the file.
  unsigned int num;
  fread(&num, sizeof(int), 1, infptr);
  // Print the number of characters obtained by using the PrintNumberChar function
  // Do not use your own print functions
  PrintNumberChar(num, outfptr);
  // After getting the Huffman tree and number of character from the header file as in last assignment,
  // we will decode the rest the file as explained in README and will print each character in the `outfile`.
  // Thus, this function have 3 prints into the outfile - printing Huffman tree using Tree_print function
  // (same as in last assignment), then printing number of characters using PrintNumberChar
  // function (same as in previous assignment using) and then printing each decoded character into
  // the outfile.
  TreeNode *node = head;
  int x;
  unsigned char bit;
  unsigned char curbyte;
  unsigned char whichbit;
  fread(&x, sizeof(char), 1, infptr);
  
  while (num)
  {
    if (!(node->right || node->left))
    {
      fprintf(outfptr, "%c", node->value);
      num--;
      node = head;
    }
    readBit(infptr, &bit, &whichbit, &curbyte);
    if (bit)
    {
      node = node->right;
    }
    else
    {
      node = node->left;
    }
    
  }

  // free up the memory
  Tree_destroy(head);
  fclose(infptr);
  fclose(outfptr);
  return 1;
}
#endif
