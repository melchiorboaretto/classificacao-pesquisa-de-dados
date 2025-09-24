#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "utils.h"
#include "sorts.h"

#define N_ALGOs 5                                                               // Qtd de algoritmos a serem testados
#define QTD_ARRAYS 3                                                            // quantidade de arrays a serem processados (1 por tipo)
#define POTENCIAS 5                                                             // potências de 10 a serem testadas como tamanhos de arrays

struct algo_info{
  char name[15];
  char acronym[5];
  void (*function)(int*, int, struct log_info*);
};

struct array_info{
  char name[15];
  char type;
  int* contents;
};

void bubblesort(int*, int, struct log_info*);
void quicksort(int*, int, struct log_info*);
void quicksort_aux(int*, int, int, struct log_info*);
int particiona(int*, int, int, struct log_info*);
void swap(int *, int *);

int main(void){
  int info_total = N_ALGOs*3*(POTENCIAS-2);
  struct algo_info algoritmos[N_ALGOs];                                                // array de structs que armazenam as funções dos algoritmos a testar
  struct array_info arrays[3];                                                         // array de informações sobre arrays a serem processados
  struct log_info *results = malloc(sizeof(struct log_info)*info_total);                      // armazena resultados do processamento de um algoritmo em um array
  struct log_info log;                                                                 // armazena contadores de comparações e trocas, além do tempo
  int* tmp_array;
  clock_t t;
  int i, algo, arr, size, potencia, result;
  FILE* file;

  // inicializa array com informações sobre os algoritmos a serem testados
  strcpy(algoritmos[0].name, "Bubblesort");
  strcpy(algoritmos[0].acronym, "BBST");
  algoritmos[0].function = &bubblesort;

  strcpy(algoritmos[1].name, "Quicksort");
  strcpy(algoritmos[1].acronym, "QQST");
  algoritmos[1].function = &quicksort;

  strcpy(algoritmos[2].name, "Combsort");
  strcpy(algoritmos[2].acronym, "CBST");
  algoritmos[2].function = &combsort;

  strcpy(algoritmos[3].name, "Shakesort");
  strcpy(algoritmos[3].acronym, "SKST");
  algoritmos[3].function = &shakesort;

  strcpy(algoritmos[4].name, "BetterQuickSort");
  strcpy(algoritmos[4].acronym, "BQST");
  algoritmos[4].function = &better_quicksort;

  srand(42);                                                                    // inicializa gerador de números aleatórios
  result = 0;

  // cria e inicializa arrays de diferentes tamanhos
  for(potencia=2;potencia<POTENCIAS;potencia++){
    size = (int)pow(10.0, (float)potencia);

    strcpy(arrays[0].name, "Crescente");
    arrays[0].type = 'C';
    arrays[0].contents = (int*) malloc(sizeof(int)*size);
    strcpy(arrays[1].name, "Decrescente");
    arrays[1].type = 'D';
    arrays[1].contents = (int*) malloc(sizeof(int)*size);
    strcpy(arrays[2].name, "Randômico");
    arrays[2].type = 'R';
    arrays[2].contents = (int*) malloc(sizeof(int)*size);

    for(i=0;i<size;i++){
      arrays[0].contents[i] = i+1;                                              // array decrescente
      arrays[1].contents[i] = size-i;                                           // array decrescente
      arrays[2].contents[i] = rand() % size;                                    // array aleatório
    }

    // testa algoritmos com os arrays
    tmp_array = (int*) malloc(sizeof(int)*size);
    for(arr=0;arr<QTD_ARRAYS;arr++){
      printf("Array %s de tamanho %d gerado: ", arrays[arr].name, size);
      for(i=0;i<size;i++) printf("%d ", arrays[arr].contents[i]);
      printf("\n");

      for(algo=0; algo<N_ALGOs; algo++){
        printf("\nOrdenando array por %s...\n", algoritmos[algo].name);
        memcpy(tmp_array, arrays[arr].contents, sizeof(int)*size);

        t = clock();
        algoritmos[algo].function(tmp_array, size, &results[result]);
        results[result].tempo = ((double)(clock()-t))/CLOCKS_PER_SEC;           // tempo decorrido (em segundos)

        printf("\nArray ordenado: ");
        for(i=0;i<size;i++) printf("%d ", tmp_array[i]);

        printf("\nQuantidade de trocas: %d", results[result].trocas);
        printf("\nQuantidade de comparações: %d", results[result].comparacoes);
        printf("\nTempo de processamento: %f segundos\n", results[result].tempo);

        strcpy(results[result].sigla, algoritmos[algo].acronym);
        results[result].tipo = arrays[arr].type;
        results[result].tamanho = size;
        result++;
      }
      printf("\n");
    }
    printf("\n");

    free(tmp_array);
    for(arr=0;i<QTD_ARRAYS;arr++) free(arrays[arr].contents);
  }

  file = fopen("results.txt", "w");
  // printf("Algoritmo - Array -  Tamanho - Comparações -    Trocas   -  Tempo (s)\n");
  printf("Algo. | Arr. type | Arr. size |   Trocas   | Comparações | Tempo (microssegundos)\n");
  fprintf(file, "Algo. | Arr. type | Arr. size |   Trocas   | Comparações | Tempo (microssegundos)\n");
  for(i=0;i<info_total;i++){
    //printf("%9s - %5c - %8d - %11d - %11d - %10.7f\n", results[i].sigla, results[i].tipo, results[i].tamanho, results[i].comparacoes, results[i].trocas, results[i].tempo);
    printf("%5s - %-9c - %9d - %10d - %11d - %10.7f\n",
      results[i].sigla,
      results[i].tipo,
      results[i].tamanho,
      results[i].comparacoes,
      results[i].trocas,
      results[i].tempo);
    fprintf(file, "%5s | %-9c | %9d | %10d | %11d | %10.7f\n",
      results[i].sigla,
      results[i].tipo,
      results[i].tamanho,
      results[i].comparacoes,
      results[i].trocas,
      results[i].tempo);
  }
  fclose(file);

  return 0;
}

