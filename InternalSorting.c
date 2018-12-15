#include <stdio.h>
#include "InternalSorting.h"

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}


int internalPartition (int v[], int low, int high){
    int pivot = v[high];
    int i = (low-1);
    for (int j = low; j <= high-1; j++){
        if (v[j] >= pivot){
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i+1], &v[high]);
    return (i+1);
}


void internalQuickSort(int v[], int low, int high){
    if (low < high){
        int pi = internalPartition(v, low, high);

        internalQuickSort(v, low, pi - 1);
        internalQuickSort(v, pi + 1, high);
    }
}


void insertionSort(int v[], int size){
    int key, j;
    for (int i = 1; i < size; i++){
       key = v[i];
       j = i-1;
       while (j >= 0 && v[j] > key){
           v[j+1] = v[j];
           j--;
       }
       v[j+1] = key;
   }
}
