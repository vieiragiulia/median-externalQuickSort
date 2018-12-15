#include <stdio.h>
#include <stdlib.h>

#include "Library.h"


void readNumber(FILE *file, int *number){
    fscanf(file, "%d", number);
}


void writeNumber(FILE *file, int *number){
    fprintf(file, "%d ", *number);
}


float getMedian(int size, char *filename){
    FILE *file = fopen(filename, "r");
    float m = 0;

    if(size%2 != 0){ //se for um número ímpar de elementos
        for(int i = 0; i < (size/2)+1; i++){ //andamos até a metade e pegamos o do meio
            fscanf(file, "%f", &m);
        }
    }

    else{
        float n = 0;
        for(int i = 0; i < (size/2)+1; i++){
            if(i != (size/2))fscanf(file, "%f", &m);
            else fscanf(file, "%f", &n);
        }
        m += n;
        m /=2;
    }
    fclose(file);
    return m;
}


float getAverage(int size, char *filename){
    FILE *file = fopen(filename, "r");
    float aux, a = 0;

    for(int i = 0; i < size; i++){
        fscanf(file, "%f", &aux);
        a += aux;
    }
    a /= size;
    
    fclose(file);
    return a;
}


void separateLine(int sizeOfLine, FILE *file){
    FILE *temp = fopen("temp", "w-r");
    int n;

    for(int i = 0; i < sizeOfLine; i++){
        fscanf(file, "%d", &n);
        fprintf(temp,"%d ", n);
    }
    fclose(temp);
}
