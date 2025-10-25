#pragma once
#include <stdint.h>

struct log_info{
  uint64_t comparacoes;
  uint64_t trocas;
  double tempo;
  int tamanho;
  char sigla[5];
  char tipo;
};

void swap(int *n1, int *n2){
	int troca = *n1;
	*n1 = *n2;
	*n2 = troca;
}

