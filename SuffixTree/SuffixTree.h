//
// Created by Chandler Roe on 11/26/17.
//

#ifndef SUFFIXTREE_SUFFIXTREE_H
#define SUFFIXTREE_SUFFIXTREE_H

#endif //SUFFIXTREE_SUFFIXTREE_H
#define alphabetSize 5

#ifndef suffixTree.h
#define suffixTree_h

struct suffixNode{
    suffixNode * children[alphabetSize];
    bool isend;
    int ID;
    int start;
    int end;

};

int * fasta_charcount(FILE * fin, int grt_num);

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


int chartoASCII(char c);


#endif
