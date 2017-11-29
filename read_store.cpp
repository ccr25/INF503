#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main() {

ifstream file("test.txt");
string content;
int x;
int count=0;
int size;
char head[40][60];
char geno[40][40];
char buffer[40];
while(file >> content) {
	x=content.find(">");
	//printf("%d\n",x);

if (x==0){
	
	strcpy(geno[count],content.c_str());
	//cout << geno[count] <<"\n";
	//buffer[60]=NULL;
	count++;
	
} else if (x!=0){
	//x=content.find(">");

	//strcpy(head[count],content.c_str());
	strcpy(buffer,content.c_str());

	//size= strlen(head[count]);
	//cout << buffer <<"\n";
	//cout << "size of this sting is "<<size <<"\n";
		
}
	strcat(head[count],buffer);
	
}
strcat(head[count],buffer);
cout << head[2] <<"\n";
//printf("number of genos is %d",count);
file.close(); 
return 0;
}
