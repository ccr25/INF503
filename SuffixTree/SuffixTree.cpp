//
// Created by Chandler Roe on 11/26/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include "suffixTree.h"
#include <iostream>
//#define FILENAME "DENV2.txt"
#define N 100
#define num 50000 // number of 36-mers
#define arraysize(a) sizeof(a)/sizeof(a[0])
//#define alphabet (5) //possible node for children.


using namespace std;

int * fasta_charcount(FILE * fin, int grt_num){

        int count,i, lin_count;
        char line[buffer];
        i=0;
        lin_count = 0;
        count = 0;

    int * count_array = (int *)calloc(grt_num,sizeof(int));

    while(!fin.eof()){                   

        while (getline(fin, line); 
    
    
    //printf("line = %s\n, length = %lu\n",line, strlen(line));
    
        if (line[0] == '>'){
            lin_count++;
        }
        else
        {   
            
        //printf("line_count = %d\n", lin_count);
        count_array[lin_count-1] = count_array[lin_count-1] + strlen(line) - 1;       
        }
    
    }
     
    fseek(fin,0,SEEK_SET);

    return count_array;
}



//constructor
void Suffix_Tree::suffix_tree(char * contig, int contigSize, suffixNode *root) {
    cout<<"contig = "<<contig<<"\n";
    //suffixNode *root = Suffix_Tree::createNode();
    // store them in a tree
        for (int i = 0; i < contigSize; i++) {
            char * splitContig = new char [i+1];


            strncpy(splitContig, contig + contigSize -1 -i, i+1);
            printf("%s\n", splitContig);
            Suffix_Tree::insert(root, splitContig, i + 1);
        }
}

char * Suffix_Tree::readFileFunction() {

    string line;

    //string subLineToAddToNode;
    ifstream inReadsFile("/Users/croe/Desktop/viralDatabase.fasta");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] != '>') {
                    char * subLineToReturn = new char[13];
                    strcat(subLineToReturn, line.c_str());
                    std::cout<<"sub line: "<<subLineToReturn<<"\n";
                    return subLineToReturn;
                }
            }
        }
    }
}



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
    else if ((int)c==78){
        return 4;
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
// We don't need int count in our project, it counts number of nodes in the tree.
void Suffix_Tree::insert(struct suffixNode *root, const char *contig, int length) {

    int i;
    //int length = strlen(contig);
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
bool Suffix_Tree::search(struct suffixNode *root, const char *contig, int mismatchValue, int length)
{
    int i;
    int count = 0;
    int index;
    struct suffixNode *p = root;
    for (i = 0; i < length; i++)
    {
        index = chartoASCII(contig[i]);

        if (!p->children[index]) {
            count++;
            cout<<"count equals: "<<count<<"\n";
            if (count > mismatchValue) {
                return false;
            }
            }
        p = p->children[index];
    }
    return (p!= NULL && p->isend);
}

//destructor
/*~Suffix_Tree::suffix_tree() {
    delete []root;
}*/
