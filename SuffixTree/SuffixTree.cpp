//
// Created by Chandler Roe on 11/26/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fstream>
#include "SuffixTree.h"
#include <iostream>
#include <vector>

using namespace std;

void concatGenomes(int grt_num, char ** header_array, char ** count_array, int * ID_array){

    int count,i, lin_count;
    string line;
    i=0;
    lin_count = 0;
    count = 0;
    ifstream fin("/Users/croe/Desktop/viralDatabase.fasta");
    char * found;
    int iD;
    int size;
    char IDBuffer[20];
    while(!fin.eof()){
        while (std::getline(fin, line)) {
            //printf("line = %s\n, length = %lu\n",line, strlen(line));
            if (line[0] == '>') {
                //cout<<"line: "<<line<<"\n";
                string line2 = line;
                strcpy(header_array[lin_count], line2.c_str());
                found = strchr(header_array[lin_count], '-');
                iD = found - header_array[lin_count] + 1;
                size = std::strlen(found);
                strncpy(IDBuffer, header_array[lin_count] + iD, size);
                ID_array[lin_count] = atoi(IDBuffer);
                //cout<<"ID is "<<ID_array[lin_count]<<"\n";

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

            //printf("line = %s\n, length = %lu\n", line.c_str(), std::strlen(line.c_str()));

            if (line[0] == '>') {
                lin_count++;
            } else {
                //printf("line_count = %d\n", lin_count);
                count_array[lin_count - 1] = count_array[lin_count - 1] + std::strlen(line.c_str());
            }
        }
    }
    inDatabase.seekg(0, ios::beg);

    return count_array;
}
//TODO::make sure to change the value back to 29!!
//constructor creates an array containing all possible kmers for the genome and populates the array.
void Suffix_Tree::build_tree(suffixNode *root,char ** genome_array, int ID) {
    //suffixNode *root = Suffix_Tree::createNode();
    // store them in a tree
    int size;
    size= strlen(genome_array[ID]);
    for (int i = 29; i < size; i++) {
        char split [i+1];
        strncpy(split, genome_array[ID] +size-i-1, 30);
        cout<<split<<"\n";
        Suffix_Tree::insert(root, split,genome_array,size-i, ID);
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
/*char * Suffix_Tree::readFileFunction() {
    string line;
    ifstream inReadsFile("/Users/croe/Desktop/viralDatabase.fasta");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] != '>') {
                    char * subLineToReturn = new char [20000];
                    strcat(subLineToReturn, line.c_str());
                    //std::cout<<"sub line: "<<subLineToReturn<<"\n";
                    cout<<"Sub line to return: "<<subLineToReturn<<"\n";
                    return subLineToReturn;
                }
            }
        }
    }

}*/

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
    struct suffixNode *pN = nullptr;
    pN = (struct suffixNode *)malloc(sizeof(struct suffixNode));
    if (pN)
    {
        int i;
        pN->isend = false;
        for (i = 0; i < alphabetSize; i++)
            pN->children[i] = nullptr;
    }
    return pN;
}

// insert a new sequence to the tree
// We don't need int count in our project, it counts number of nodes in the tree.
// insert a new sequence to the tree
void Suffix_Tree::insert(struct suffixNode *root, const char *sequence,char **genome_array, int position, int ID) {

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
        index = charToASCII(sequence[gothrough]);
        if (!p->children[index]){
            p->children[index] = createNode();
            p=p->children[index];
            p->ID = ID;
            p->	start = position+gothrough-1;
            p-> end = position +length-2;
            //cout<<"I got a new node lol"<<"\n";
            cout<<"number 1 to see pushback"<<"\n";
            cout<<"ID is: "<<ID<<"\n";
            p->IDlist.insert(p->IDlist.end(), ID);
            cout<<"node ID is: "<<p->ID<<"\n";

            return;
        }else{
            // if we do have the node, we compare them
            int *temp;
            p=p->children[index];
            int size_of_nodestr=p->end-p->start+1;
            char node_str[size_of_nodestr];
            int ID_value = p->ID;
            strncpy(node_str, (genome_array[ID_value] + p->start), size_of_nodestr);
            //cout<<"node str is "<<node_str<<"\n";
            substr_len=length-gothrough;
            //cout<<"we there #1"<<"\n";
            if (size_of_nodestr<substr_len){
                for (j=0;j<size_of_nodestr;j++){
                    if (node_str[j]!=sequence[gothrough+j]){
                        //char temp_substr1[length-j];
                        //char temp_substr2[size_of_nodestr-j];
                        //cout<<"we there #2"<<"\n";
                        int previous_end;

                        p->end=p->start+gothrough+j-1;
                        previous_end = p->end+1;
                        //cout<<"previous_end "<<previous_end<<"\n";
                        index1=charToASCII(node_str[gothrough+j]);
                        index2=charToASCII(sequence[gothrough+j]);
                        p->children[index1] = createNode();
                        struct suffixNode *temp1 = p->children[index1];
                        temp1->start=previous_end;
                        temp1->end =previous_end+size_of_nodestr-j-1;
                        //temp1->ID = ID;
                        p->children[index2] = createNode();
                        struct suffixNode *temp2 = p->children[index2];
                        //cout<<"j is "<<j<<"\n";
                        //cout<<"length is "<<length<<"\n";
                        temp2->start=position-1+gothrough+j ;
                        temp2->end =position+length-2;
                        temp2->ID = ID;
                        cout<<"number 2 to see pushback"<<"\n";
                        temp2->IDlist.insert(temp2->IDlist.end(), ID);
                        cout<<"node ID is: "<<temp2->ID<<"\n";
                        return;
                    }
                }

                gothrough=gothrough+size_of_nodestr;

            } else{
                //cout<<"we there #3"<<"\n";
                for (j=0;j<substr_len;j++){
                    if (node_str[j]!=sequence[gothrough+j]){
                        //char temp_substr1[length-j];
                        //char temp_substr2[size_of_nodestr-j];
                        int previous_end;
                        p->end=p->start+gothrough+j-1;
                        previous_end = p->end+1;
                        index1=charToASCII(node_str[gothrough+j]);
                        index2=charToASCII(sequence[gothrough+j]);
                        p->children[index1] = createNode();
                        struct suffixNode *temp1 = p->children[index1];
                        temp1->start=previous_end;
                        temp1->end =previous_end+size_of_nodestr-j-1;
                        //temp1->ID = ID;
                        //temp1->IDlist->push_back(ID);
                        p->children[index2] = createNode();
                        struct suffixNode *temp2 = p->children[index2];
                        //cout<<"j is "<<j<<"\n";
                        //cout<<"length is "<<length<<"\n";
                        temp2->start=position-1+gothrough+j ;
                        temp2->end =position+length-2;
                        temp2->ID = ID;
                        temp2->IDlist.insert(temp2->IDlist.end(), ID);
                        cout<<"node ID is: "<<temp2->ID<<"\n";
                        return;
                    }

                }
                p->IDlist.insert(p->IDlist.end(), ID);
                cout<<"node ID is: "<<p->ID<<"\n";
                return;
            }

        }
    }

    p->IDlist.insert(p->IDlist.end(), ID);
    cout<<"node ID is: "<<p->ID<<"\n";
    return;
    //cout<<"childd start "<<p->	start<<"\n";
    //cout<<"childd end "<<p->	end<<"\n";
    /*p-> end = position +i+length-2;
    cout<<" start is "<< p->start <<"\n";
    cout<<" end is "<< p->end <<"\n";
    cout<<"we didn't have a new node'"<<"\n";

    cout<<"next node start"<<p->start <<"\n";*/
}

// search a sequence if it is presneted in the tree or not. return 0 for not presented, 1 for presented;
vector<int> Suffix_Tree::search(struct suffixNode *root, const char *sequence,char ** genome_array)
{
    int i;
    int length = strlen(sequence);
    int index;
    int gothrough=0;
    struct suffixNode *p = root;
    while (gothrough<length)
    {
        cout<<"go through is "<<gothrough<<"\n";
        index = charToASCII(sequence[gothrough]);
        cout<<"we there #3  "<<"\n";
        if (!p->children[index]) {
            cout<<"we there #2  "<<"\n";
            return {};
        }else {
            cout<<"we there #1 "<<"\n";
            p=p->children[index];
            cout<<"this is hi:"<<"\n";

            int size_of_nodestr=p->end - p->start +1;
            int size_of_substr=length-gothrough;
            int IDValue = p->ID;

            char node_str[size_of_nodestr];
            snprintf(node_str,size_of_nodestr+1,genome_array[IDValue]+p->start);
            //cout<<"node string is "<<node_str<<"\n";
            if (size_of_nodestr<size_of_substr){
                for (i=0;i<size_of_nodestr;i++){
                    if (node_str[i]!=sequence[gothrough+i]){
                        return {};
                    }
                }
                gothrough=gothrough+size_of_nodestr;

            } else{
                for (i=0;i<size_of_substr;i++){
                    if (node_str[i]!=sequence[gothrough+i]){
                        return {};
                    }
                }
                cout<<"Found::"<<"\n";
                return p->IDlist;
            }

        }
        cout<<"we there #4 "<<"\n";

    }
    cout<<"Found1::"<<"\n";
    return p->IDlist;         //(p!= NULL && p->isend);
}
struct readNode {
    int locationInRead;
    int readNumber;
    readNode * next;
    string readSeedSequence;
};

readNode * CreateReadNode() {
    readNode *newNode = new readNode;
    newNode->next = NULL;
    return newNode;
}

//function will retrieve the number of lines in the multifasta file
/*int retrieveNumberOfLines () {
    string line;
    int number_of_lines = 0;
    //ifstream inReadsFile("/Users/croe/Desktop/test_reads.fasta");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] != '>') {
                    number_of_lines++;
                }
            }
        }
    }
    inReadsFile.close();
    return number_of_lines;
}*/

readNode ** populateReadsFileArray( readNode ** readsFile, int kmerSize, int readLength) {
    string line;
    long double radix_value_to_add;
    int readNumber = 1;
    //int countfirstNode = 0;
    //int countNextNode = 0;
    int steppingSize = (readLength - kmerSize) + 1;
    string subLineToAddToNode;
    ifstream inReadsFile("/Users/croe/Desktop/test_reads.fasta");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] != '>') {
                    int counter = 0;
                    while (counter < steppingSize) {
                        subLineToAddToNode = line.substr(counter, kmerSize);
                        readNode * newReadNode = CreateReadNode();
                        newReadNode->readSeedSequence = subLineToAddToNode;
                        //cout<<"read kmer sequence: "<<subLineToAddToNode<<"\n";
                        newReadNode->readNumber= readNumber;
                        //cout<<"read number: "<<readNumber<<"\n";
                        counter++;
                    }
                    readNumber++;
                }
            }
        }
    }
    inReadsFile.close();
    return readsFile;
}

void printTree(suffixNode * root, char ** genome_array) {
    suffixNode * x = root;
   suffixNode * p = x->children[0];
    for (int i = 0; i < 5; i++) {
        cout<<"node zero is : "<<p->children[3]->start<<"\n";
        for(int j = 0; j < 5; j++) {

            if (p->children[0]->children[j] == nullptr) {
                cout << "the child is: " << j << " " << "Yes" << "\n";
                //cout<<"node start is : "<<p->children[0]->start<<"\n";
                //cout<<"node end : "<<p->children[0]->end<<"\n";

            }else{
                cout<<"NOT NULL "<<j<<" "<<p->children[0]->children[j]->start<<"\n";
            }
        }
        cout<<"end is : "<<p->children[3]->end<<"\n";
        cout<<"the letter is : "<<genome_array[p->children[3]->ID][p->children[3]->start]<<"\n";


       // p = p->children[3];
    }
}


//destructor
/*~Suffix_Tree::suffix_tree() {
    delete []root;
}*/
