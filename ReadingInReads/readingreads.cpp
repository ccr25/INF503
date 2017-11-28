//
// Created by Chandler Roe on 11/27/17.
//

#include <iostream>
#include <fstream>

using namespace std;

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
int retrieveNumberOfLines () {
    string line;
    int number_of_lines;
    number_of_lines = 0;
    ifstream inReadsFile("/Users/croe/Desktop/hw_dataset.fa");
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
}

readNode ** populateReadsFileArray( readNode ** readsFile, int kmerSize, int readLength) {
    string line;
    long double radix_value_to_add;
    int readNumber = 1;
    //int countfirstNode = 0;
    //int countNextNode = 0;
    int steppingSize = (readLength - kmerSize) + 1;
    string subLineToAddToNode;
    ifstream inReadsFile("/Users/croe/Desktop/hw_dataset.fa");
    if (inReadsFile.is_open()) {
        while (!inReadsFile.eof()) {
            while (getline(inReadsFile, line)) {
                if (line[0] != '>') {
                    int counter = 0;
                    while (counter < steppingSize) {
                        subLineToAddToNode = line.substr(counter, kmerSize);
                        readNode * newReadNode = CreateReadNode();
                        newReadNode->readSeedSequence = subLineToAddToNode;
                        cout<<"read kmer sequence: "<<subLineToAddToNode<<"\n";
                        newReadNode->readNumber= readNumber;
                        cout<<"read number: "<<readNumber<<"\n";
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
