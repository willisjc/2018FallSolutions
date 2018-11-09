/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw16.h"

/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_FREETREE
// FreeBinaryTree
// This function frees up the memory from the root node

void FreeBinaryTree(treeNode *root)
{
    if(root)
    {
        FreeBinaryTree(root->leftChild);
        FreeBinaryTree(root->rightChild);
        free(root);
    }
}

#endif

#ifdef TEST_SEARCH
// This function recursively searches for a given value in a tree
// and returns the node which has that value
treeNode *search(treeNode *tn, int value)
{
    if (tn)
    {
        if (value == tn->value)
        {
            return tn;
        }
        treeNode *rc = search(tn->rightChild, value);
        treeNode *lc = search(tn->leftChild, value);
        return (rc ? rc : lc);
    }
    return NULL;
}

#endif

#ifdef TEST_SUBTREE
/* This function checks if `needle` is subtree of `haystack`. By subtree, it means that all the values of
*  `needle` are in `haystack`. For example in Example 1 (README),
*  treeNode with value 10 in Tree1 is subtree of Tree2 but Tree1 is not subtree of Tree2 . Please note this function is different from `isContained`,
* as it recursively compares two Trees/subtrees from the treeNodes given as input.
* It is consistent with  strstr function in C i.e. "strstr(const char \*haystack, const char \*needle)"
*/
bool isSubTree(treeNode *haystack, treeNode *needle)
{
    if (!needle || !haystack) {
        return false;
    }
    treeNode * nRc = needle->rightChild;
    treeNode * nLc = needle->leftChild;
    treeNode * hRc = haystack->rightChild;
    treeNode * hLc = haystack->leftChild;
    if (nRc) {
        if (!hRc) {
            return false;
        }
    }
    if (nLc) {
        if (!hLc) {
            return false;
        }
    }
    return((haystack->value == needle->value) && (nLc?isSubTree(hLc, nLc):true) && (nRc?isSubTree(hRc, nRc):true));
}
#endif

#ifdef TEST_CONTAINED
// returns true if needle is contained in haystack
// returns false if needle is not contained in haystack
// needle and haystack may NOT be binary search tree
// Please note that order of arguments are important
// It is consistent with  strstr function in C i.e.
// "strstr(const char \*haystack, const char \*needle)"
bool isContained(treeNode *haystack, treeNode *needle)
{
    if (!haystack || !needle)
    {
        return false;
    }
    if (needle->value == haystack->value)
    {
        return isSubTree(haystack,needle);
    }
    return (isContained(haystack->leftChild, needle) || isContained(haystack->rightChild, needle));
}

#endif
