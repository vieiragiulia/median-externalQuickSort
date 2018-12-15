#include "ExternalSorting.h"


void topReading(FILE **readTop, int *rt, int *thisNumber, int *swap){
		char aux = fgetc(*readTop);
		while(aux != ' '){
				fseek(*readTop,-1,SEEK_CUR);
				aux = fgetc(*readTop);
				fseek(*readTop,-1,SEEK_CUR);
		}
    fseek(*readTop, 0, SEEK_SET); //coloca o ponteiro no inicio
    for(int i = 0; i <= (*rt); i++) readNumber(*readTop, thisNumber); //le o buffer do arquivo
    *rt = *rt-1; //desce o apontador de leitura superior
    *swap = 0; //sinaliza que a próxima será leitura inferior
  }


void bottomReading(FILE **readBottom, int *rb, int *thisNumber, int *swap){
		readNumber(*readBottom, thisNumber); //le o buffer do arquivo
		*rb = *rb+1; //sobe o apontador de leitura inferior
		*swap = 1; //sinaliza que a próxima será leitura superior
}


void writeMax(FILE **writeTop, int *thisNumber, int *wt){
    double aux = (double)*thisNumber;
    fseek(*writeTop, (int)log10(aux)+1, SEEK_CUR);
    writeNumber(*writeTop, thisNumber); //escreve o buffer no arquivo
    fseek(*writeTop, (int)log10(aux)+1, SEEK_CUR);
    *wt = *wt-1;//desce o apontador de escrita superior
}


void writeMin(FILE **writeBottom, int *thisNumber, int *wb){
		writeNumber(*writeBottom, thisNumber); //escreve o buffer no arquivo
		*wb = *wb+1; //sobe o apontador de escrita inferior
}


void fillMemory(FILE **readBottom, FILE **readTop, int *memory, int *usedMemory, int nIntMem, int *swap, int *rb, int *rt){
		//enquando a memória ainda não está toda cheia ou ainda não chegamos no meio do arquivo
		while(*usedMemory <= nIntMem && *rt >= *rb){ //lemos alternadamente de baixo e de cima e guarda
				if(*swap == 0) bottomReading(readBottom, rb, &memory[*usedMemory], swap);
				else topReading(readTop, rt, &memory[*usedMemory], swap);
				*usedMemory = *usedMemory+1;
		}
}


void moveNumber(FILE **writeHere, int position, int thisNumber, int *memory, int *w){
		if(position == 0) writeMin(writeHere, &memory[position], w); //escrita superior
		else writeMax(writeHere, &memory[position], w); //escrita inferior
		//substituímos o topo da memória pelo número atual
		memory[position] = thisNumber;
}


void externalPartition(int left, int right, FILE **readBottom, FILE **readTop, FILE **writeTop, FILE **writeBottom, int *memory, int nIntsMem, int *i, int *j){
		//cria variáveis de orientação no arquivo para cada uma das possibilidades, bottom = min = left, top = max = right
		int rb = left;
		int rt = right;
		int wb = left;
		int wt = right;
		//ajusta os ponteiros inferiores para as posições corretas
		int thisNumber;
		fseek(*writeBottom, 0, SEEK_SET);
    fseek(*writeTop, 0, SEEK_END);
    fseek(*readBottom, 0, SEEK_SET);
    fseek(*readTop, 0, SEEK_END);

		int usedMemory = 0;
		int swap = 0;

		*i = left-1;
		*j = right+1;


		fillMemory(readBottom, readTop, memory, &usedMemory, nIntsMem, &swap, &rb, &rt);
		internalQuickSort(memory, 0, usedMemory-1);

		while(rt >= rb){ //enquanto houverem números a serem lidos
				//lê o prox número sem sobrescrever
				if(rt == wt+1) topReading(readTop, &rt, &thisNumber, &swap); //se lemos de cima onde escrevemos
				else if(rb == wb-1) bottomReading(readBottom, &rb, &thisNumber, &swap); //se lemos de baixo onde escrevemos
				else if(swap == 0) bottomReading(readBottom, &rb, &thisNumber, &swap); //se lemos de cima da última vez
				else topReading(readTop, &rt, &thisNumber, &swap);//se lemos de baixo da última vez
				//opções de lugares de alocação da memória nova
				if(thisNumber < memory[0]){ //vem antes do mínimo, coloca por cima
						*i = wb;
						writeMin(writeBottom, &thisNumber, &wb);
				}
				else if(thisNumber > memory[usedMemory- 1]){//vem depois do máximo, coloca por baixo
						*j = wt;
						writeMax(writeTop, &thisNumber, &wt);
				}
				else{ //entre o max e o min
						//verificamos qual apontador andou mais até então
						if(wb - left > right - wt) moveNumber(writeBottom, 0, thisNumber, memory, &wb); //se foi o escrita superior
						else moveNumber(writeTop, nIntsMem - 1, thisNumber, memory, &wt);	//se foi o escrita inferior
						insertionSort(memory, usedMemory); //ordena memória porque trocamos elementos
			}
		}

		for(int k = 0; k < usedMemory; k++) writeMin(writeBottom, &memory[k], &wb); //descarrega memória no arquivo

		fflush(*readBottom);
		fflush(*readTop);
		fflush(*writeBottom);
		fflush(*writeTop);
}


void externalQuickSort(int right, int left, FILE **readBottom, FILE **readTop, FILE **writeTop, FILE **writeBottom, int *memory, int nIntsMem){
		if(right - left < 1) return;
		int i, j; //novo left e novo right

		externalPartition(left, right, readBottom, readTop, writeTop, writeBottom, memory, nIntsMem, &i, &j);

		externalQuickSort(i, right, readBottom, readTop, writeTop, writeBottom, memory, nIntsMem);
		externalQuickSort(left, j, readBottom, readTop, writeTop, writeBottom, memory, nIntsMem);
}


void sort(int sizeOfLine, int nIntsMem, char *nameInput){
		//cria os ponteiros que vão andar no arquivo de cima para baixo ou de baixo para cima para escrever/ler
		FILE *readBottom = fopen(nameInput, "r+b"); if(!readBottom){ printf("this input doesnt exist\n"); exit(1);}
		FILE *readTop = fopen(nameInput, "r+b"); if(!readTop){ printf("this input doesnt exist\n"); exit(1);}
		FILE *writeBottom = fopen(nameInput, "r+b"); if(!writeBottom){ printf("this input doesnt exist\n"); exit(1);}
		FILE *writeTop = fopen(nameInput, "r+b"); if(!writeTop){ printf("this input doesnt exist\n"); exit(1);}
		//cria o vetor de memória que guarda os elementos a serem inseridos/ordenados
		int *memory = (int*)calloc(nIntsMem, sizeof(int));

		externalQuickSort(sizeOfLine-1, 0, &readBottom, &readTop, &writeTop, &writeBottom, memory, nIntsMem-1);

		fclose(readBottom);
		fclose(readTop);
		fclose(writeBottom);
		fclose(writeTop);

		free(memory);
}
