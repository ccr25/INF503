#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;

struct readNode {
    int locationInRead;
    int readNumber;
    readNode * next;
    string readSeedSequence;
    //long double radix_value;
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

/*long double radix_converstion(string instring, int kmerSize) {
    long double str_value, base_value;
    //cout<<"instring: "<<"\n";
    //cout <<"radix_conversion_string: "<< instring << "\n";
    //cout << instring.length() << "\n";
    str_value = 0;
    for (int i=0; i < instring.length(); i++)
        //cout << i << '\n';
        if (instring[i] == 'A') {
            base_value = (0 * pow(4, (kmerSize-i)));
            str_value += base_value;
        }
        else if (instring[i] == 'C') {
            base_value = (1 * pow(4, (kmerSize-i)));
            str_value += base_value;
        }
        else if (instring[i] == 'G') {
            base_value = (2 * pow(4, (kmerSize-i)) );
            str_value += base_value;
        }
        else if (instring[i] == 'T') {
            base_value = (3 * pow(4, (kmerSize-i)));
            str_value += base_value;
        }
        else {
            cout<<"instring i: "<<instring[i]<<"\n";
            cout<<"i is: "<<i<<"\n";
            cout << "test_poop\n";//' << '\n';
        }
    return str_value;
}*/

readNode ** populateReadsFileArray( readNode ** readsFile, int kmerSize, int readLength) {
    string line;
    long double radix_value_to_add;
    int readNumber = 1;
    int countfirstNode = 0;
    int countNextNode = 0;
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
                            //radix_value_to_add = radix_converstion(subLineToAddToNode, kmerSize);
                            readNode * newReadNode = CreateReadNode();
                            //newReadNode->radix_value = radix_value_to_add;
                            //cout<<"radix value to add: "<<radix_value_to_add<<"\n";
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

int main() {

    //Figure out the number of reads in a file
    int numberOfLines = retrieveNumberOfLines();
    int readLength = 50;
    //cout<<"Number of lines is: "<<numberOfLines<<"\n";
    int kmerSize = 30;
    int numberOfReadSeeds = (numberOfLines * kmerSize );

    readNode ** slavasReadsNodeArray = new readNode * [numberOfReadSeeds];
    populateReadsFileArray(slavasReadsNodeArray, kmerSize, readLength);

    return 0;
}
