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
void Suffix_Tree::suffix_tree(char * contig, int contigSize, suffixNode *root, int ID, char ** genome_array ) {
    //cout<<"contig = "<<contig<<"\n";
    //suffixNode *root = Suffix_Tree::createNode();
    // store them in a tree
    cout<<"contig size outside of loop: "<<contigSize<<"\n";
    for (int i = 0; i < contigSize; i++) {
        cout<<"i is what: "<<i<<"\n";
        char * splitContig = new char [i+1];
        strncpy(splitContig, contig + contigSize -1 -i, i+1);
        printf("contig going in %s\n", splitContig);
        Suffix_Tree::insert(root, splitContig, i + 1, ID, contigSize -i -1, genome_array, contigSize);
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

void Suffix_Tree::branchTree(suffixNode * parentNode, int j, int i, int currentChild, char ** genome_array, const char * contig, int ID, int startValue, int length, int totalLength) {

    cout<<"are we in branch tree?"<<"\n";
    suffixNode * temp1 = createNode();
    cout<<"temp1 start is: "<<parentNode->children[currentChild]->start<<"\n";
    temp1->start = parentNode->children[currentChild]->start;
    temp1->end = parentNode->children[currentChild]->start + (j - parentNode->children[currentChild]->start);
    cout<<"temp1 end value is: "<<parentNode->children[currentChild]->start + (j - parentNode->children[currentChild]->start)<<"\n";
    temp1->ID = parentNode->children[currentChild]->ID;
    cout<<"are we past first chunk?"<<"\n";

   //Gets character for start value of old node
    //TODO::NEEDS WORK
    int newStart = charToASCII(genome_array[parentNode->children[currentChild]->ID][parentNode->children[currentChild]->start + (j - 2)]);
    cout<<"what is j: "<<j<<"\n";
    cout<<"parent node child start: "<<parentNode->children[currentChild]->start<<"\n";
    cout<<"parent node ID: "<<parentNode->children[currentChild]->ID<<"\n";
    cout<<"genome array: "<<genome_array[0][2]<<"\n";
    //cout<<"char to ascii is:"<<charToASCII()
    cout<<"new start: "<<newStart<<"\n";

    temp1->children[newStart] = parentNode->children[currentChild];
    temp1->children[newStart]->start = temp1->children[newStart]->start + j - 1;
    parentNode->children[currentChild] = temp1;
    cout<<"are we past second chunk?"<<"\n";

    suffixNode * temp2 = createNode();
    cout<<"contig j:"<<contig[i]<<"\n";
    int checkValues = charToASCII(contig[i]);
    temp1->children[checkValues] = temp2;
    cout<<"what is our ascii value: "<<checkValues<<"\n";
    temp2->start = startValue + j - 1;
    temp2->end = totalLength;
    temp2->ID = ID;
    temp2->isend = true;
    cout<<"are we past third chunk?"<<"\n";

}

// insert a new sequence to the tree
// We don't need int count in our project, it counts number of nodes in the tree.
int Suffix_Tree::insert(struct suffixNode *root, const char *contig, int length, int ID, int startValue, char ** genome_array, int totalLength) {

    cout << "initial length: " << length << "\n";
    cout<<"initial start value: "<<startValue<<"\n";

    int index;
    int count = 0;
    struct suffixNode *p = root;
    int i = 0;
    while (i < length) {
        //cout<<"start\n";
        //cout<<"i equals at start "<<i<<"\n";
        index = charToASCII(contig[i]);
        int keepTrackOfNode = charToASCII(genome_array[ID][startValue + 1]);
        if (p->children[index] == nullptr) {

            cout << "whole contig: " << contig << "\n";
            cout << "whole length: " << length << "\n";
            p->children[index] = createNode();
            p->children[index]->ID = ID;
            p->children[index]->start = startValue + i;
            p->children[index]->end = totalLength;
            p->children[index]->isend = true;
           return 0;
        } else {
            suffixNode *currentNode = p->children[index];
            // if (currentNode->isend == false) {
            cout << "we suck, cool\n";
            cout << "the end value: " << p->children[index]->end << "\n";
            cout << "i in first: " << i << "\n";
            //checks length of node sequence against remaining contig length
            cout << "current end minus current start: " << currentNode->end - currentNode->start << "\n";
            cout << "length: " << length << "\n";
            cout << "start value: " << currentNode->start << "\n";
            cout << "end value: " << currentNode->end << "\n";
            if (currentNode->end - currentNode->start < length - i) {
                cout << "if start value: " << currentNode->start << "\n";
                cout << "if end value: " << currentNode->end << "\n";
                for (int j = currentNode->start; j < currentNode->end; j++) {
                    cout << "what is j: " << j << "\n";
                    cout << "we suck\n";
                    if (genome_array[currentNode->ID][j] == contig[i]) { //if the bases match, continue
                        i++;

                    }
                    else { //if the bases don't match, split the node up and create a new node.
                        //TODO::make this a separate function on its own that we call here.
                        cout << "where are we" << "\n";
                        Suffix_Tree::branchTree(p, j, i, keepTrackOfNode, genome_array, contig, ID, startValue,
                                                length, totalLength);



                        return 0;

                    }

                }

                    char *subContig = new char[length-i];

                    strncpy(subContig, contig + i, length - i);
                    cout<<"running insert 2nd time\n";
                    cout<<"substring here "<<subContig<<"\n";
                    cout<<"start value before recursion is: "<<startValue<<"\n";
                    insert(currentNode, subContig, length - i, ID, startValue , genome_array,totalLength);
                    cout<<"the length minus i is: "<<length - i<<"\n";
                    return 0;
            }
            else{
                cout<<"is this our problem???"<<"\n";
            }
        /*}

                else{

                int j = p->children[index]->start;
            //cout<<"i in first: "<<i<<"\n";
                while(i < length){
                    /*cout<<"i in first: "<<i<<"\n";
                    cout<<"genome_array: "<<genome_array[p->children[index]->ID][j]<<"\n";
                    cout<<"contig: "<<contig[i]<<"\n";
                    cout<<"j is: "<<j<<"\n";
                    cout<<"i is: "<<i<<"\n";
                    cout<<"whole contig: "<<contig<<"\n";

                    if (genome_array[p->children[index]->ID][j] == contig[i]) {

                        i++;
                        j++;
                    }
                    else {
                        cout<<"howdy "<<"\n";
                        p->children[index]->children[keepTrackOfNode] = createNode();
                        p->children[index]->children[keepTrackOfNode]->ID = ID;
                        p->children[index]->children[keepTrackOfNode]->start = startValue + j;
                        p->children[index]->children[keepTrackOfNode]->end = length;
                        p->children[index]->children[keepTrackOfNode]->isend = true;
                        p->children[index]->isend = false;
                        p->children[index]->end = j;
                        break;
                    }



                }

            int keepTrackOfNode = charToASCII(genome_array[p->children[index]->ID][p->children[index]->start + i]);
            p->children[index] = p->children[index]->children[keepTrackOfNode];
        }
}

if (p->children[index]->isend == true) {

    int keepTrackOfNode = charToASCII(genome_array[p->children[index]->ID][p->children[index]->start + i]);
    for (int k = p->children[index]->start; k < length; k++) {
       cout<<"really, we do"<<"\n";
        cout<<"genome_array: "<<genome_array[p->children[index]->ID][k]<<"\n";
        cout<<"contig: "<<contig[i]<<"\n";
        cout<<"k is: "<<k<<"\n";
        cout<<"i is: "<<i<<"\n";
        cout<<"whole contig: "<<contig<<"\n";
        if (genome_array[p->children[index]->ID][k] == contig[i]) {
            i++;
        } else {
            cout<<"this should kill it\n";
            p->children[index]->children[keepTrackOfNode] = createNode();
            p->children[index]->children[keepTrackOfNode]->ID = ID;
            p->children[index]->children[keepTrackOfNode]->start = startValue + k;
            p->children[index]->children[keepTrackOfNode]->end = length;
            p->children[index]->children[keepTrackOfNode]->isend = true;
            p->children[index]->isend = false;
            p->children[index]->end = k;
            break;
        }
    }
}
}*/
                }
            }
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
    //return (p!= NULL && p->isend);
    return true;
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
