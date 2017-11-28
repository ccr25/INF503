#include <iostream>
#include <fstream>
#include <math.h>
#include "ReadingReads.h"

int main() {

    //Figure out the number of reads in a file
    int numberOfLines = retrieveNumberOfLines();
    int readLength = 50;
    //cout<<"Number of lines is: "<<numberOfLines<<"\n";
    int kmerSize = 30;
    int numberOfReadSeeds = (numberOfLines * kmerSize );


    /*//create the 2D array to store my input reads
    char ** readsFile = new char *[numberOfLines];
    for (int i = 0; i <= numberOfLines; i++) {
        readsFile[i] = new char[51];
    }*/

    readNode ** slavasReadsNodeArray = new readNode * [numberOfReadSeeds];
    populateReadsFileArray(slavasReadsNodeArray, kmerSize, readLength);

    return 0;
}
