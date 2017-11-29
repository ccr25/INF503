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

using namespace std;

void concatGenomes(int grt_num, char ** header_array, char ** count_array){

    int count,i, lin_count;
    string line;
    i=0;
    lin_count = 0;
    count = 0;
    ifstream fin("/Users/croe/Desktop/viralDatabase.fasta");

    while(!fin.eof()){
        while (std::getline(fin, line)) {
            //printf("line = %s\n, length = %lu\n",line, strlen(line));
            if (line[0] == '>') {
                cout<<"line: "<<line<<"\n";
                string line2 = line;
                strcpy(header_array[lin_count], line2.c_str());
                //cout<<"header array is: "<<header_array[lin_count]<<"\n";
                lin_count++;



            } else {
                const char * tester = line.c_str();
                //printf("line_count = %d\n", lin_count);
                //cout<<"1header array is: "<<header_array[0]<<"\n";
                strcat(count_array[lin_count -1], line.c_str());
                //cout<<"2 header array is: "<<header_array[0]<<"\n";
            }
        }
    }

    //fseek(fin,0,SEEK_SET);
    fin.seekg(0, ios::beg);
}

int * fasta_charcount(int grt_num) {

    string line;
    int count, i, lin_count;
    i = 0;
    lin_count = 0;
    count = 0;
    ifstream inDatabase("/Users/croe/Desktop/viralDatabase.fasta");

    int *count_array = (int *) calloc(grt_num, sizeof(int));

    while (!inDatabase.eof()) {

        while (getline(inDatabase, line)) {

            printf("line = %s\n, length = %lu\n", line.c_str(), std::strlen(line.c_str()));

            if (line[0] == '>') {
                lin_count++;
            } else {
                printf("line_count = %d\n", lin_count);
                count_array[lin_count - 1] = count_array[lin_count - 1] + std::strlen(line.c_str());
            }
        }
    }
        inDatabase.seekg(0, ios::beg);

        return count_array;
    }

//constructor creates an array containing all possible kmers for the genome and populates the array.
void Suffix_Tree::suffix_tree(char * contig, int contigSize, suffixNode *root) {
    //cout<<"contig = "<<contig<<"\n";
    //suffixNode *root = Suffix_Tree::createNode();
    // store them in a tree
        for (int i = 0; i < contigSize; i++) {
            char * splitContig = new char [i+1];
            strncpy(splitContig, contig + contigSize -1 -i, i+1);
            //printf("%s\n", splitContig);
            Suffix_Tree::insert(root, splitContig, i + 1);
        }
}

//function to read in the database multifasta file and return the number of genomes in the database based on '>'.
int readNumberOfGenomesInDatabase() {

    string line;
    int counter = 0;
    ifstream inReadsFile("/Users/croe/Desktop/viralDatabase.fasta");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] == '>') {
                    counter++;
                }
            }
        }
    }
    return counter;
}

//function to read in the database multifasta file and populate the 2D array with each genome.
char * Suffix_Tree::readFileFunction() {
    string line;
    ifstream inReadsFile("/Users/croe/Desktop/viralDatabase.fasta");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] != '>') {
                    char * subLineToReturn = new char [13];
                    strcat(subLineToReturn, line.c_str());
                    //std::cout<<"sub line: "<<subLineToReturn<<"\n";
                    return subLineToReturn;
                }
            }
        }
    }
}

//function converts nucleotide bases 'A', 'C', 'G', 'T' into ascii values for easier comparison. Returns ascii value.
int charToASCII(char c){
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

//function creates new suffix tree nodes with all children set to null and returns the new node.
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
        index = charToASCII(contig[i]);
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
        index = charToASCII(contig[i]);

        if (!p->children[index]) {
            count++;
            //cout<<"count equals: "<<count<<"\n";
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
