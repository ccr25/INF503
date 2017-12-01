//
// Created by Chandler Roe on 11/26/17.
//

#ifndef SUFFIXTREE_SUFFIXTREE_H
#define SUFFIXTREE_SUFFIXTREE_H

#endif //SUFFIXTREE_SUFFIXTREE_H
#define alphabetSize 5

#ifndef suffixTree.h
#define suffixTree_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <vector>

//using namespace std;

struct suffixNode{
    suffixNode * children[alphabetSize];
    bool isend;
    int ID;
    int start;
    int end;

};

class Suffix_Tree {

    suffixNode * root;

public:
    //void set_subject_into_tree(char *, int size);
    //void suffix_tree();
    static void suffix_tree(char * contig, int contigSize,suffixNode *root);
    //void ~suffix_tree();

    static void insert(struct suffixNode *root, const char *contig, int length);
    static bool search(struct suffixNode *root, const char *contig, int mismatchValue, int length);
    static suffixNode * createNode();
    static char * readFileFunction();
    //bool querry_trace(char *, int size);

};

int * fasta_charcount(int grt_num);
void concatGenomes(int grt_num, char ** header_array, char ** count_array, int * ID_array);
int charToASCII(char c);
int readNumberOfGenomesInDatabase();


#endif
