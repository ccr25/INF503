#include <iostream>
#include "suffixTree.h"

using namespace std;


int main() {
 int cool;
    suffixNode * root= Suffix_Tree::createNode();
    const char * subStr = "TGC";
    char * tester = new char[13];
    tester = Suffix_Tree::readFileFunction();
    Suffix_Tree::suffix_tree(tester, 13, root);
    cool = Suffix_Tree::search(root, subStr, 1, 3);

    cout<<"search = "<<cool<<"\n";
}
