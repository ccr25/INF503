// classes example
#include <iostream>
#define alphabetSize 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <time.h>
#define FILENAME "DENV2.txt"
#define N 10
#define num 50000 // number of 36-mers
#define arraysize(a) sizeof(a)/sizeof(a[0])
using namespace std;

struct suffixNode{
    suffixNode * children[alphabetSize];
    bool isend;
    int start;
    int end;
};
int chartoASCII(char c){
    if ((int)c==65){
        return 0;
    }
    else if ((int)c==67){
        return 1;
    }
    else if ((int)c==71){
        return 2;
    }
    else if ((int)c==84){
        return 3;
    }
};
class Suffix_Tree {

    suffixNode * root;

public:

    static void build_tree(suffixNode *root,char * contig);
    //void ~suffix_tree();
    static void insert(struct suffixNode *root, const char *contig,const char *geno,int position ) ;
    static bool search(struct suffixNode *root, const char *contig );
    static suffixNode * createNode();

};

void Suffix_Tree::build_tree(suffixNode *root,char * sequence) {
    //suffixNode *root = Suffix_Tree::createNode();
    // store them in a tree
    int size;
    size= strlen(sequence);
        for (int i = 0; i < size; i++) {
            char split [i+1];
            snprintf(split, i +2, sequence +size-i-1);
    		//cout<<split<<"\n";
            Suffix_Tree::insert(root, split,sequence,size-i);
        }
}

suffixNode * Suffix_Tree::createNode()
{
    struct suffixNode *pN = NULL;	
    pN = (struct suffixNode *)malloc(sizeof(struct suffixNode));
    if (pN)
    {
        int i;
        pN->isend = false;
        for (i = 0; i < alphabetSize; i++)
            pN->children[i] = NULL;
    }
    return pN;
}
// insert a new sequence to the tree
void Suffix_Tree::insert(struct suffixNode *root, const char *sequence,const char *geno, int position) {
	
    int i,j;
	
    int length = strlen(sequence);
    int index,index1,index2;
    struct suffixNode *p = root;
    cout<<" position is "<< position -1  <<"\n";
    for (i = 0; i < length; i++)
    {

        index = chartoASCII(sequence[i]);
        if (!p->children[index]){
            p->children[index] = createNode();
            p=p->children[index];
            p->	start = position+i-1;
            p-> end = position +i+length-2;
            cout<<"I got a new node lol"<<"\n";
            return;
        }else{
		int *temp;
		
		p=p->children[index];
		int size_of_nodestr=p->end-p->start+1;
		char node_str[size_of_nodestr];
		snprintf(node_str,size_of_nodestr+1,geno+p->start);
		cout<<"node str is "<<node_str<<"\n";
		if (size_of_nodestr<length){
			for (j=1;j<size_of_nodestr;j++){
				if (node_str[j]!=sequence[j]){
					//char temp_substr1[length-j];
					//char temp_substr2[size_of_nodestr-j];
					int previous_end;
					p->end=p->start+j-1;
					previous_end = p->end+1;
					index1=chartoASCII(node_str[j]);
					index2=chartoASCII(sequence[j]);
					p->children[index1] = createNode();
					struct suffixNode *temp1 = p->children[index1];
					temp1->start=previous_end;
					temp1->end =previous_end+size_of_nodestr-j-1;
					p->children[index2] = createNode();
					struct suffixNode *temp2 = p->children[index2];
					temp2->start=j;
					temp2->end =length-1;
					return;
				}
			}
		}
		
		//cout<<"childd start "<<p->	start<<"\n";
		//cout<<"childd end "<<p->	end<<"\n";
    	/*p-> end = position +i+length-2;
    	cout<<" start is "<< p->start <<"\n";
    	cout<<" end is "<< p->end <<"\n";
        cout<<"we didn't have a new node'"<<"\n";
		
		cout<<"next node start"<<p->start <<"\n";*/
	}
    }
    p->isend = true;
}

//destructor
//~Suffix_Tree::suffix_tree() {
//    delete []root;
//}


// search a sequence if it is presneted in the tree or not. return 0 for not presented, 1 for presented;
bool Suffix_Tree::search(struct suffixNode *root, const char *sequence)
{
    int i;
    int count = 0;
    int length = strlen(sequence);
    int index;

    struct suffixNode *p = root;
    for (i = 0; i < length; i++)
    {
    	p->start = i;
    	p->end=length-1;
        index = chartoASCII(sequence[i]);
        if (!p->children[index]) {
        	
                return false;
            }
        p = p->children[index];
    }
    return true;         //(p!= NULL && p->isend);
}


int main(){
 	char s[15000];
	ifstream file(FILENAME);
	string content;
	while(file >> content) {
		strcat(s,content.c_str());	
	} 	
	//cout<<s<<"\n";
	time_t tm;
	srand((unsigned) time(&tm));
	int number,i,cool;
	char x[N];
	int a=strlen(s);
	for (i=0;i<num;i++){
	number = rand() % a-N+1;	 
	strncpy(x, s+number, N);
	}	
	//cout<<x<<"\n";
	
	char tester2[]= "TTCGAG";
	//snprintf(tester,17,tester2);
	//cout<<tester<<"\n";

	 char * subStr = "TACG";
	suffixNode * root= Suffix_Tree::createNode();
	Suffix_Tree::build_tree(root,tester2);
	cout<<"root start "<<root->children[1]->start<<"\n";
	cout<<"root end  "<<root->children[1]->end<<"\n";
	cout<<"root start "<<root->children[2]->children[0]->start<<"\n";
	cout<<"root end  "<<root->children[1]->children[0]->end<<"\n";
	/*cool = Suffix_Tree::search(root, subStr);
	cout<<cool<<"\n";*/
	
    
    
}



