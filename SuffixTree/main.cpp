#include <iostream>
#include "suffixTree.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;


int main() {

    int anotherCool;
    int cool;
    suffixNode * root= Suffix_Tree::createNode();
    /*const char * subStr = "TATACTCTCTATATAACGTGCATGCATCGA";
    const char * subStrTst2 = "ATATTCCCTCTCTCCCCCTTTATATATATA";
    char * tester2 = "CTATCTCTAATTATATTCCCTCTCTCCCCCTTTATATATATA";
    char * tester = new char[36];
    tester = "TTTCTATATACTCTCTATATAACGTGCATGCATCGA";
    Suffix_Tree::suffix_tree(tester, 36, root);
    Suffix_Tree::suffix_tree(tester2, 42, root);
    cool = Suffix_Tree::search(root, subStr, 0, 30);
    anotherCool = Suffix_Tree::search(root, subStrTst2, 0, 30);*/
    //cout<<"search number: "<<cool<<"\n";
    //cout<<"search anotherCool is: "<<anotherCool<<"\n";

    int numbRGenomes;
    int * intArray;
    std::ifstream inReadFile("/Users/croe/Desktop/viralDatabase.fasta");
    //open the multifasta database and count how many genomes are going to be loaded into the tree, return that number
    numbRGenomes = readNumberOfGenomesInDatabase();
    //cout<<"Number of Genomes in Database: "<<numbRGenomes<<"\n";

    intArray = fasta_charcount(numbRGenomes);
    char ** header_array = new char *[numbRGenomes];
    int * ID_array = new int [numbRGenomes];
    char ** genome_array = new char * [numbRGenomes];
    for (int i= 0; i < numbRGenomes; i++) {
        genome_array[i] = new char [intArray[i]];
        header_array[i] = new char[200];
        //cout<<"int array is: "<<intArray[i]<<"\n";
    }

    concatGenomes(numbRGenomes, header_array, genome_array, ID_array);

//This converts
    vector<pair<int,char*>> vect;
    vector<pair<int,int>> vect1;


    for (int i = 0; i < numbRGenomes;i++) {
        vect.push_back(make_pair(ID_array[i], genome_array[i]));
        vect1.push_back(make_pair(ID_array[i], intArray[i]));
    }

    std::sort(vect.begin(), vect.end());
    std::sort(vect1.begin(), vect1.end());

    for (int i = 0; i < numbRGenomes; i++) {

        ID_array[i] = vect[i].first;
        genome_array[i] = vect[i].second;
        intArray[i] = vect1[i].second;

       /* cout<<"ID array sorted: "<<ID_array[i]<<"\n";
        cout<<"INt array sorted: "<<intArray[i]<<"\n";

        cout<<"header array: "<<header_array[i]<<"\n";
        cout<<"count array: "<<genome_array[i]<<"\n";*/

    }

    //gets size of genomes to make the count_array


    char tester[] = "CTAGAGAGAGAGAGAAGAGAGAGAAGAGAGAGAGAG";
    char tester2[] = "AGAGAGAGAGAGAGAGAGAGAGAGAGAGAGAGA";
    char tester3[] = "GGGGGCTCTCTCTCTCTCTCTCTCTCTCTCTCTCT";
    char tester4[] = "AAAAAACTCTCTCTCTCTCTCTCTCTCTCTCTCTCT";
    char * subStr = "CTCTCTCTCTCTCTCTCTCTCTCTCTCTCT";
    char ** genome_test_array = new char *[4];
    for (int i = 0; i < 4; i++) {
        genome_test_array[i] = new char [36];
    }

    strcpy(genome_test_array[0], tester);
    strcpy(genome_test_array[1], tester2);
    strcpy(genome_test_array[2], tester3);
    strcpy(genome_test_array[3], tester4);
    cout<<"This is the genome array 0: "<<genome_test_array[0]<<"\n";
    cout<<"This is the genome array 1: "<<genome_test_array[1]<<"\n";

    //Suffix_Tree::build_tree(root, tester, );

        //cout<<" contig size = "<[i]<<"\n";
    Suffix_Tree::build_tree(root, genome_test_array, 0 );
    Suffix_Tree::build_tree(root, genome_test_array, 1 );
    Suffix_Tree::build_tree(root, genome_test_array, 2);
    Suffix_Tree::build_tree(root, genome_test_array, 3);

    // A for 0, C for 1, G for 2, T for 3.
	cout<<"root start first generation "<<root->children[1]->start<<"\n";
	cout<<"root end first generation "<<root->children[1]->end<<"\n";
    cout<<"root end first generation "<<root->children[1]->ID<<"\n";
	/*cout<<"root start second generation "<<root->children[3]->children[3]->start<<"\n";
	cout<<"root end second generation "<<root->children[3]->children[3]->end<<"\n";
	cout<<"root start third generation"<<root->children[3]->children[3]->children[1]->start<<"\n";
	cout<<"root end third generation "<<root->children[3]->children[3]->children[1]->ID<<"\n";
	/*cout<<"root start forth generation"<<root->children[1]->children[1]->children[1]->children[1]->start<<"\n";
	cout<<"root start forth generation"<<root->children[1]->children[1]->children[1]->children[1]->end<<"\n";
    cool = Suffix_Tree::search(root, subStr,tester);
    cout<<cool<<"\n";*/


    cout<<"Is this working?"<<"\n";

    vector<int> cool1 = Suffix_Tree::search(root, subStr, genome_test_array);
    cout<<"Does this print: "<<"\n";
    for (int i = 0; i < cool1.size(); i++) {
        cout<<cool1[i]<<"\n";
    }
    cout<<"Size of vector: "<<cool1.size()<<"\n";

    //printTree(root, genome_array);
    //char searcher[] = "CG";
    //cool = Suffix_Tree::search(root, searcher, 0, 2);
    //cout<<"searcher results: "<<cool<<"\n";

    /*//Suffix_Tree::suffix_tree((tryViralDatabase, ))
    //Read the database file in, populating a 2D array with all of the genomes, return this array
    /*tester = Suffix_Tree::readFileFunction();
    Suffix_Tree::suffix_tree(tester, 36, root);
    cool = Suffix_Tree::search(root, subStr, 0, 30);
    //cout<<"search = "<<cool<<"\n";

    //Figure out the number of reads in a file
    //int numberOfLines = retrieveNumberOfLines();
    /*int readLength = 100;
    cout<<"Number of lines is: "<<numberOfLines<<"\n";
    int kmerSize = 30;
    int totalNumberSize = (readLength - kmerSize + 1)
    int numberOfReadSeeds = (numberOfLines * totalNumberSize );


    /create the 2D array to store my input reads
    char ** readsFile = new char *[numberOfLines];
    for (int i = 0; i <= numberOfLines; i++) {
        readsFile[i] = new char[51];
    }

    //readNode ** slavasReadsNodeArray = new readNode * [numberOfReadSeeds];
    //populateReadsFileArray(slavasReadsNodeArray, kmerSize, readLength);

     vector<pair<int,char*> > vect;
     for (int i = 0; i < numbRGenomes;i++){
         vect.push_back(make_pair(ID_array[i], count_array[i]));
     }
     for (int i = 0; i < numbRGenomes; i++) {
         cout << "vect1: " << vect[i].first << "\n";
         //cout<<"header ar ray: "<<header_array[i]<<"\n";
         cout << "vect2: " << vect[i].second << "\n";
     }
     std::sort(vect.begin(), vect.end());
     for (int i = 0; i < numbRGenomes; i++) {
         cout<<"vect1 sorted: "<<vect[i].first<<"\n";
         //cout<<"header ar ray: "<<header_array[i]<<"\n";
         cout<<"vect2 sorted: "<<vect[i].second<<"\n";
     }*/


}
