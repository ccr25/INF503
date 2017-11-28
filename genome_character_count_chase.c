#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * fasta_charcount(FILE * fin, int buffer, int grt_num){

		int count,i, lin_count;
		char line[buffer];
		i=0;
		lin_count = 0;
		count = 0;
	
		int * count_array = (int *)calloc(grt_num,sizeof(int));
		int c = 0;

	while(fgets(line,buffer,fin) != NULL){

//	fgets(line,buffer,fin); 
	
	
	printf("line = %s\n, length = %lu\n",line, strlen(line));
	
		if (line[0] =='>'){
			lin_count++;
			
		}
		else
		{	
			
		printf("line_count = %d\n", lin_count);		
		count_array[lin_count-1] = count_array[lin_count-1] + strlen(line) - 1;	
		}	
				
	}		
		
	fseek(fin,0,SEEK_SET);

	return count_array;
}



int main(int argc, char ** argv){

char * filename = argv[1];

FILE *hwfile = fopen(filename, "r");


int * cool = fasta_charcount(hwfile, 500, 30);

for(int i = 0; i < 30; i++){

	printf("sequence %d is: %d\n", i, cool[i]);

}



		}
