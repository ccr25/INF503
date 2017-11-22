#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define FILENAME "DENV2.txt"
#define N 100
#define num 50000 // number of 36-mers
#define arraysize(a) sizeof(a)/sizeof(a[0])
#define alphabeta (4) //possible node for children.
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
struct Node
{
    struct Node *children[alphabeta];
    bool isend;
};
struct Node *findnode(void)
{
    struct Node *pN = NULL;
    pN = (struct Node *)malloc(sizeof(struct Node));
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
int insert(struct Node *root, const char *queires, int count)
{
    int i;
    int length = strlen(queires);
    int index;
    struct Node *p = root;
    for (i = 0; i < length; i++)
    {
        index = chartoASCII(queires[i]);
        if (!p->children[index]){
            p->children[index] = findnode();
            count++;
		}
        p = p->children[index];
    }
    p->isend = true;
    return count;
} 

// search a sequence if it is presneted in the tree or not. return 0 for not presented, 1 for presented;
bool search(struct Node *root, const char *queires)
{
    int i;
    int length = strlen(queires);
    int index;
    struct Node *p = root;
    for (i = 0; i < length; i++)
    {
        index = chartoASCII(queires[i]);
 
        if (!p->children[index])
            return false;
 
        p = p->children[index];
    }
    return (p!= NULL && p->isend);
}

int main()
{
    char results[][15] = {"Not presented", "Presented"};
 	char s[156*N];
	char str[N];
	char feq[num][37]; // num of random 36 mers. 
 	int i,ii,a;
 	int count=0;
	char x[37];
	FILE *fp = fopen(FILENAME, "r");
// creation of the num of random 36-mers
	for (i=0;i<156;i++){
		fgets(str, N, fp);
		strtok(str, "\n");
			strcat(s, str);
	}
	time_t tm;
	srand((unsigned) time(&tm));
	int number;
	a=strlen(s);
	for (ii=0;ii<num;ii++){
	number = rand() % 10713;
	strncpy(x, s+number, 36);
	strcpy(feq[ii],x);
	}
    struct Node *root = findnode();
    
    // store them in a trie
    for (i = 0; i < arraysize(feq); i++)
       {
	   	count=insert(root, feq[i],count);  
		} 
		
	//printf("the size of trie for %d number of 36-mers is %d ",num,count);
	
    printf("%s is %s in tire\n", "ATCTTCGAGACACTGCGGACCGACAAAGACAGATTC", results[search(root, "ATCTTCGAGACACTGCGGACCGACAAAGACAGATTC")] );
    printf("%s is %s in trie\n", "GAGTGATGGTTATGGTAGGCGCCACTATGACGGATG", results[search(root, "GAGTGATGGTTATGGTAGGCGCCACTATGACGGATG")] );
    printf("%s is %s in trie\n", "ACGAGATGGGTTTCCTAGAAAAAACGAAGAAAGATT", results[search(root, "ACGAGATGGGTTTCCTAGAAAAAACGAAGAAAGATT")] );
    printf("%s is %s in trie\n", "CCCATATATGCCCTCAGTCATAGAAAAAATGGAAGC", results[search(root, "CCCATATATGCCCTCAGTCATAGAAAAAATGGAAGC")] );

}
