#ifndef INTERNALSORTING_H
#define INTERNALSORTING_H

#include "Library.h"


void swap(int *a, int *b);
//troca a e b de endereço um com o outro

int internalPartition (int v[], int low, int high);
//partição do quicksort

void internalQuickSort(int v[], int low, int high);
//quicksort

void insertionSort(int v[], int size);
//insertionsort

#endif
