#ifndef EXTERNALSORTING_H
#define EXTERNALSORTING_H

#include <string.h>
#include <math.h>

#include "InternalSorting.h"


void topReading(FILE **readTop, int *rt, int *thisNumber, int *swap);
/*lê o próximo número de cima para baixo*/

void bottomReading(FILE **readBottom, int *rb, int *thisNumber, int *swap);
/*lê o prox número de baixo para cima*/

void writeMax(FILE **writeTop, int *thisNumber, int *wt);
/*escreve o número onde está wt e desce wt*/

void writeMin(FILE **writeBottom, int *thisNumber, int *wb);
/*escreve o número onde está wb e sobe wb*/

void fillMemory(FILE **readBottom, FILE **readTop, int *memory, int *usedMemory, int nIntMem, int *swap, int *rb, int *rt);
/*preenche memory com elementos do arquivo alternadamente do início e do final*/

void moveNumber(FILE **writeHere, int position, int thisNumber, int *memory, int *w);
/*insere thisNumber em memory, se position = 0, escreve no arquivo por baixo, se não, por cima*/

void externalPartition(int left, int right, FILE **readBottom, FILE **readTop, FILE **writeTop, FILE **writeBottom, int *memory, int nIntsMem, int *i, int *j);
/*preenche o vetor na memória primária e enquanto houverem elementos disponíveis escreve-os:
1. embaixo se forem menores que o menor da memória primária
2. em cima se forem maiores que o maior da memória primária
3. substituindo alguém na memória primária, se estiverem em seu intervalo de alcance*/

void externalQuickSort(int right, int left, FILE **readBottom, FILE **readTop, FILE **writeTop, FILE **writeBottom, int *memory, int nIntsMem);
/*igual ao quicksort interno, chama a partição e a si mesma para a esquerda e para a direita*/

void sort(int sizeOfLine, int nIntsMem, char *nameInput);
/*inicializa os ponteiros de leitura e escrita (por cima e por baixo) no arquivo
aloca um vetor do tamanho da memória disponível para uso para guardar os números
chama o quicksort externo, fecha os arquivos e libera a memória usada no vetor*/

#endif
