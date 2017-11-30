#include <iostream>
#include "suffixTree.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

using namespace std;


int main() {

    int anotherCool;
    int cool;
    suffixNode * root= Suffix_Tree::createNode();
    const char * subStr = "TATACTCTCTATATAACGTGCATGCATCGA";
    const char * subStrTst2 = "ATATTCCCTCTCTCCCCCTTTATATATATA";
    char * tester2 = "CTATCTCTAATTATATTCCCTCTCTCCCCCTTTATATATATA";
    char * tester = new char[36];
    tester = "TTTCTATATACTCTCTATATAACGTGCATGCATCGA";
    Suffix_Tree::suffix_tree(tester, 36, root);
    Suffix_Tree::suffix_tree(tester2, 42, root);
    cool = Suffix_Tree::search(root, subStr, 0, 30);
    anotherCool = Suffix_Tree::search(root, subStrTst2, 0, 30);
    cout<<"search number: "<<cool<<"\n";
    cout<<"search anotherCool is: "<<anotherCool<<"\n";

    int numbRGenomes;
    int * intArray;
    //std::ifstream inReadFile("/Users/croe/Desktop/viralDatabase.fasta");
    //open the multifasta database and count how many genomes are going to be loaded into the tree, return that number
    numbRGenomes = readNumberOfGenomesInDatabase();
    //cout<<"Number of Genomes in Database: "<<numbRGenomes<<"\n";

   /* intArray = fasta_charcount(numbRGenomes);
    char ** header_array = new char *[numbRGenomes];
    char ** count_array = new char * [numbRGenomes];
    for (int i= 0; i < numbRGenomes; i++) {
        count_array[i] = new char [intArray[i]];
        header_array[i] = new char[200];
        cout<<"int array is: "<<intArray[i]<<"\n";
    }

    concatGenomes(numbRGenomes, header_array, count_array);
    for (int i = 0; i < numbRGenomes; i++) {
        cout<<"header array: "<<header_array[1]<<"\n";
        cout<<"count array: "<<count_array[i]<<"\n";

    }


    //Read the database file in, populating a 2D array with all of the genomes, return this array
    tester = Suffix_Tree::readFileFunction();
    Suffix_Tree::suffix_tree(tester, 13, root);
    cool = Suffix_Tree::search(root, subStr, 1, 3);
    //cout<<"search = "<<cool<<"\n";*/


}
