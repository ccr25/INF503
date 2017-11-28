#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
void main()
{
 char s[10][20];
 char result[10][20];
 char test[20];
 int counter;
 int i=0;
 int count=0;
 int x;
 FILE *fp;
 char **Hash = (char**)malloc(10*sizeof(char*));
 fp = fopen("test.txt","r");
 for(i=0;i<6;i++)
 {
  fscanf(fp,"%s",s[i]);
  //printf("%s\n",s[i]);
  x = strstr(s[i], ">");
  if (x == 0){
  	 //printf("%s\n",s[i]);
  	 counter=strlen(s[i]);
  	 count++;
  	 printf("%d\n",counter);
  }
}
printf("number of genome %d",count);
}
