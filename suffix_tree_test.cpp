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
    static bool search(struct suffixNode *root, const char *contig,const char *geno);
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
	int substr_len;
    int length = strlen(sequence);
    int gothrough = 0;
    int index,index1,index2;
    struct suffixNode *p = root;
    cout<<" position is "<< position -1  <<"\n";
    while (gothrough<length)
    {

    	//if we don't have the node, we create a new one and store start, end in this node
        index = chartoASCII(sequence[gothrough]);
        if (!p->children[index]){
            p->children[index] = createNode();
            p=p->children[index];
            p->	start = position+gothrough-1;
            p-> end = position +length-2;
            cout<<"I got a new node lol"<<"\n";
            return;
        }else{
        // if we do have the node, we compare them
		int *temp;
		p=p->children[index];
		int size_of_nodestr=p->end-p->start+1;
		char node_str[size_of_nodestr];
		snprintf(node_str,size_of_nodestr+1,geno+p->start);
		cout<<"node str is "<<node_str<<"\n";
		substr_len=length-gothrough;
		cout<<"we there #1"<<"\n";
		if (size_of_nodestr<substr_len){
			for (j=0;j<size_of_nodestr;j++){
				if (node_str[j]!=sequence[gothrough+j]){
					//char temp_substr1[length-j];
					//char temp_substr2[size_of_nodestr-j];
					cout<<"we there #2"<<"\n";
					int previous_end;
					
					p->end=p->start+gothrough+j-1;
					previous_end = p->end+1;
					cout<<"previous_end "<<previous_end<<"\n";
					index1=chartoASCII(node_str[gothrough+j]);
					index2=chartoASCII(sequence[gothrough+j]);
					p->children[index1] = createNode();
					struct suffixNode *temp1 = p->children[index1];
					temp1->start=previous_end;
					temp1->end =previous_end+size_of_nodestr-j-1;
					p->children[index2] = createNode();
					struct suffixNode *temp2 = p->children[index2];
					cout<<"j is "<<j<<"\n";
					cout<<"length is "<<length<<"\n";
					temp2->start=position-1+gothrough+j ;
					temp2->end =position+length-2;
					return;
				}
			}
			
		gothrough=gothrough+size_of_nodestr;

		} else{
			cout<<"we there #3"<<"\n";
			for (j=0;j<substr_len;j++){
				if (node_str[j]!=sequence[gothrough+j]){
					//char temp_substr1[length-j];
					//char temp_substr2[size_of_nodestr-j];
					int previous_end;
					p->end=p->start+gothrough+j-1;
					previous_end = p->end+1;
					index1=chartoASCII(node_str[gothrough+j]);
					index2=chartoASCII(sequence[gothrough+j]);
					p->children[index1] = createNode();
					struct suffixNode *temp1 = p->children[index1];
					temp1->start=previous_end;
					temp1->end =previous_end+size_of_nodestr-j-1;
					p->children[index2] = createNode();
					struct suffixNode *temp2 = p->children[index2];
					cout<<"j is "<<j<<"\n";
					cout<<"length is "<<length<<"\n";
					temp2->start=position-1+gothrough+j ;
					temp2->end =position+length-2;
					return;
					}				
				
			}
			return;
		}

		}
		}
		 
    p->isend = true;
    		//cout<<"childd start "<<p->	start<<"\n";
		//cout<<"childd end "<<p->	end<<"\n";
    	/*p-> end = position +i+length-2;
    	cout<<" start is "<< p->start <<"\n";
    	cout<<" end is "<< p->end <<"\n";
        cout<<"we didn't have a new node'"<<"\n";
		
		cout<<"next node start"<<p->start <<"\n";*/
}

//destructor
//~Suffix_Tree::suffix_tree() {
//    delete []root;
//}


// search a sequence if it is presneted in the tree or not. return 0 for not presented, 1 for presented;
/*bool Suffix_Tree::search(struct suffixNode *root, const char *sequence)
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
}*/ 

bool Suffix_Tree::search(struct suffixNode *root, const char *sequence,const char *geno)
{
    int i;
    int length = strlen(sequence);
    int index;
	int gothrough=0;
    struct suffixNode *p = root;
    while (gothrough<length)
    {
    	cout<<"go through is "<<gothrough<<"\n";
        index = chartoASCII(sequence[gothrough]);
        cout<<"we there #3  "<<"\n";
        if (!p->children[index]) {
        		cout<<"we there #2  "<<"\n";
                return false;
            }else {
            	cout<<"we there #1 "<<"\n";
            	p=p->children[index];
            	
            	int size_of_nodestr=p->end - p->start +1;
            	int size_of_substr=length-gothrough;
            	
            	char node_str[size_of_nodestr];
            	snprintf(node_str,size_of_nodestr+1,geno+p->start);
            	//cout<<"node string is "<<node_str<<"\n";
            	if (size_of_nodestr<size_of_substr){
            		for (i=0;i<size_of_nodestr;i++){
            			if (node_str[i]!=sequence[gothrough+i]){
            			return false;
						}
					}
					gothrough=gothrough+size_of_nodestr;
					
				} else{
					for (i=0;i<size_of_substr;i++){
            			if (node_str[i]!=sequence[gothrough+i]){
            			return false;
						}
					}
					return true;
				}
            	
			}
        cout<<"we there #4 "<<"\n";
        
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
	
	char tester2[]= "ATCCATCG";
	//snprintf(tester,17,tester2);
	//cout<<tester<<"\n";

	 char * subStr = "GCCAT";
	suffixNode * root= Suffix_Tree::createNode();
	Suffix_Tree::build_tree(root,tester2);
	// A for 0, C for 1, G for 2, T for 3.
//	cout<<"root start first generation "<<root->children[3]->start<<"\n";
//	cout<<"root end first generation "<<root->children[3]->end<<"\n";
//	cout<<"root start second generation "<<root->children[3]->children[2]->start<<"\n";
//	cout<<"root end second generation "<<root->children[3]->children[2]->end<<"\n";
//	cout<<"root start third generation"<<root->children[1]->children[1]->children[1]->start<<"\n";	
//	cout<<"root end third generation "<<root->children[1]->children[1]->children[1]->end<<"\n";
//	cout<<"root start forth generation"<<root->children[1]->children[1]->children[1]->children[1]->start<<"\n";
//	cout<<"root start forth generation"<<root->children[1]->children[1]->children[1]->children[1]->end<<"\n";
	cool = Suffix_Tree::search(root, subStr,tester2);
	cout<<cool<<"\n";
	
    
    
}



