#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#define FILENAME "DENV2.txt"
#define N 100
#define num 50000 // number of 36-mers
#define arraysize(a) sizeof(a)/sizeof(a[0])
#define alphabeta (5) //possible node for children.

//constructor
void suffix_Tree(const char *contig, int contigSize) {
    
    struct suffixNode *root = createNode();
    
    // store them in a trie
    for (i = 0; i < arraysize(contigSize); i++)
       {
	   	count=insert(root, contigSize[i],count);  
		} 
}

int chartoASCII(c){
	if ((int)c==65){
		return 0;
	} else if ((int)c==67){
		return 1;
	} else if ((int)c==71){
		return 2;
	} else if ((int)c==84){
		return 3;
	}
}
struct suffixNode *createNode(void)
{
    struct suffixNode *pN = NULL;
    pN = (struct suffixNode *)malloc(sizeof(struct suffixNode));
    if (pN)
    {
        int i;
        pN->isend = false;	
        for (i = 0; i < alphabeta; i++)
            pN->children[i] = NULL;
    }
    return pN;
}

// insert a new sequence to the tree
// We don't need int count in our project, it counts number of nodes in the tree.
void insert(struct suffixNode *root, const char *contig)
{
    int i;
    int length = strlen(contig);
    int index;
    struct suffixNode *p = root;
    for (i = 0; i < length; i++)
    {
        index = chartoASCII(contig[i]);
        if (!p->children[index]){
            p->children[index] = createNode();
		}
        p = p->children[index];
    }
    p->isend = true;
} 

// search a sequence if it is presneted in the tree or not. return 0 for not presented, 1 for presented;
bool search(struct suffixNode *root, const char *contig, int mismatchValue)
{
    int i;
    int count = 0;
    int length = strlen(contig);
    int index;
    struct suffixNode *p = root;
    for (i = 0; i < length; i++)
    {
        index = chartoASCII(contig[i]);
 
        if (!p->children[index])
	    count++;
	    if (count > mismatchValue)
                 return false;
 
        p = p->children[index];
    }
    return (p!= NULL && p->isend);
}

//destructor
suffix_tree::~suffix_tree() {
	delete []root;
}
