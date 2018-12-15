#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

void readNumber(FILE *file, int *number);
/*lê um número de file e aloca seu valor em number*/

void writeNumber(FILE *file, int *number);
/*escreve o número de number em file*/

float getMedian(int size, char *filename);
/*percorre o arquivo e pega o valor da mediana (para retornar), que pode ser:
1. se o tamanho size for ímpar, o valor da possição (size/2)+1
2. se o tamanho size for par, a média entre os valores size/2 e (size/2)+1*/

float getAverage(int size, char *filename);
/*percorre o arquivo e soma todos os valores, depois divide pelo número de valores (size) e retorna isso*/

void separateLine(int sizeOfLine, FILE *file);
/*pega o arquivo file e copia sizeOfLine elementos dele (neste caso, copia uma linha da entrada)
para um arquivo temporário, depois retorna o nome deste temporário*/

#endif
