//
// Created by Chandler Roe on 11/26/17.
//

#ifndef SUFFIXTREE_SUFFIXTREE_H
#define SUFFIXTREE_SUFFIXTREE_H

#endif //SUFFIXTREE_SUFFIXTREE_H
#define alphabetSize 5

#ifndef SuffixTree.h
#define SuffixTree_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <vector>

//using namespace std;

struct readNode;
readNode * CreateReadNode();
int retrieveNumberOfLines ();
readNode ** populateReadsFileArray( readNode ** readsFile, int kmerSize, int readLength);

struct suffixNode{
    suffixNode * children[alphabetSize];
    bool isend = true;
    int start;
    int end;
    int ID;
    std::vector<int> *IDList;
    std::vector<int> *startingValue;

};

class Suffix_Tree {

    suffixNode * root;

public:
    //void set_subject_into_tree(char *, int size);
    //void suffix_tree();
    static void suffix_tree(char * contig, int contigSize,suffixNode *root, int ID, char ** genome_array );
    //void ~suffix_tree();

    static void insert(struct suffixNode *root, const char *contig, int length, int ID, int startValue, char ** genome_array );
    static bool search(struct suffixNode *root, const char *contig, int mismatchValue, int length);
    static suffixNode * createNode();
    static char * readFileFunction();


};

int * fasta_charcount(int grt_num);
void concatGenomes(int grt_num, char ** header_array, char ** count_array, int * ID_array);
int charToASCII(char c);
int readNumberOfGenomesInDatabase();


#endif
