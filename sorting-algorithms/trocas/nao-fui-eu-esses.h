#include "../sortingutils.h"
// *****************************************************************************
// Funções de Ordenação

void bubblesort(int* array, int array_size, struct log_info* log){
    int trocas = 0;
    int comparacoes = 0;
    int pos_troca = 0;
    bool troca = true;
    int qtd_elementos = array_size-1;

    while(troca){
        troca = false;
        for(int i=0; i<qtd_elementos;i++){
            comparacoes = comparacoes + 1;
            if(array[i] > array[i+1]){
              swap(&array[i], &array[i+1]);
              troca = true;
              pos_troca = i;
              trocas = trocas + 1;
            }
        }
        qtd_elementos = pos_troca;
    }

    log->trocas = trocas;
    log->comparacoes = comparacoes;
}

int particiona(int* array, int esq, int dir, struct log_info* log){
  int i=esq+1, j=dir, pivo=esq;
  while(j>i){
    while(array[i]<array[pivo] && i<dir) {
      i++;
      log->comparacoes++;
    }
    while(array[j]>=array[pivo] && j>esq){
      j--;
      log->comparacoes++;
    }

    if(i<j && array[i]>array[j]){
      swap(&array[i], &array[j]);
      log->comparacoes++;
      log->trocas++;
    }
  }

  if(array[j]<array[pivo]){
	  swap(&array[pivo], &array[j]);
    log->comparacoes++;
    log->trocas++;
  }
  return j;
}

void quicksort_aux(int* array, int i, int f, struct log_info* log){
    int p;
    if(f>i){
		  p = particiona(array, i, f, log);
		  quicksort_aux(array, i, p-1, log);
		  quicksort_aux(array, p+1, f, log);
	}
}

void quicksort(int* array, int array_size, struct log_info* log){
  log->trocas = 0;
  log->comparacoes = 0;
  quicksort_aux(array, 0, array_size-1, log);
}

