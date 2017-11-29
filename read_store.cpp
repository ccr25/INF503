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
string buffer2 ="";
char buffer[60] ="";
char buffer1[60] ="";
while(file >> content) {
	x=content.find(">");
	//printf("%d\n",x);

if (x==0){
	strcpy(geno[count],content.c_str());
	//cout << geno[count] <<"\n";
	memset(buffer1, 0, 40);
	count++;
	
} else if (x!=0){
	//x=content.find(">");
	memset(buffer1, 0, 40);
	//strcpy(head[count],content.c_str());
	strcpy(buffer,content.c_str());
	strcpy(buffer1,buffer);
	//strtok(buffer1,"T");
	//size= strlen(head[count]);
	//cout << buffer <<"\n";
	//cout << "size of this sting is "<<size <<"\n";		
}
	strcat(head[count],buffer1);
}
//strcat(head[count],buffer);
cout << head[13] <<"\n";
//printf("number of genos is %d",count);
file.close(); 
return 0;
}
