#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Library.h"
#include "InternalSorting.h"
#include "ExternalSorting.h"

#define ONE_MB 1024*1024


void processMatrix(int u, int c, FILE *input, FILE *output, int nIntsMem){
    float lMedian, lAverage, average = 0;
    for(int i = 0; i < u; i++){ //para cada linha
        separateLine(c, input); //separa a linha em um arquivo temporário
        lAverage = getAverage(c, "temp"); //encontra média
        average += lAverage; //soma média à média total da matriz
        sort(c, nIntsMem, "temp"); //ordena a linha
        lMedian = getMedian(c, "temp"); //encontra median
        fprintf(output, "%.2f,%.2f\n",lAverage, lMedian); //printa média e mediana
        remove("temp");
    }
    fprintf(output, "%.2f\n", average/u); //printa média total da matriz
}


int main (int argc, char *argv[]){
    int nIntsMem;
    if(argc < 4) nIntsMem = 2;
    else nIntsMem = (atoi(argv[3])*ONE_MB)/(8*sizeof(int));

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    int u, c;
    fscanf(input, "%d", &u);
    fscanf(input, "%d", &c);

    processMatrix(u, c, input, output, nIntsMem);

    fclose(input);
    fclose(output);
    return 0;
}
