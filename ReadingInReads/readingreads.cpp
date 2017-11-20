#include <iostream>
#include <fstream>


using namespace std;

//function will retrieve the number of lines in the multifasta file
double retrieveNumberOfLines () {
    string line;
    double number_of_lines;
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

int main() {

    double numberOfLines = retrieveNumberOfLines();
    cout<<"Number of lines is: "<<numberOfLines<<"\n";

    return 0;
}
