#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * * fasta_charcount(FILE * fin, int buffer, int grt_num){

        int count,i, lin_count;
        char line[buffer];
        i=0;
        lin_count = 0;
        count = 0;

        int * count_array = (int *)calloc(grt_num,sizeof(int));
        int c = 0;

        char ** test = (char **)malloc(sizeof(char * ) * 30);

        for( int i = 0; i < 30; i++){
            test[i] = (char *)malloc(sizeof(char)*200);

        }

    while(fgets(line,buffer,fin) != NULL){

//  fgets(line,buffer,fin); 


    printf("line = %s\n, length = %lu\n",line, strlen(line));

        if (line[0] =='>'){
            lin_count++;

        }
        else
        {

        printf("line_count = %d\n", lin_count);
        count_array[lin_count-1] = count_array[lin_count-1] + strlen(line) - 1;
        strcat(test[lin_count-1],line);


        }

    }

    fseek(fin,0,SEEK_SET);

    //return count_array;

    return test;
}



int main(int argc, char ** argv){

char * filename = argv[1];

FILE *hwfile = fopen(filename, "r");
"test_genome_print.c" 72L, 1109C                                                                    1,1           Top
