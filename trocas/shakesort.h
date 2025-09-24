#include "../utils.h"

void shakesort(int *arr, int arr_size, struct log_info *log) {

    bool swapped;
    bool reverse = false;
    int indice;
    int inf = 0;
    int sup = arr_size - 1;

    do {
        swapped = false;

        if (reverse) {
            indice = sup;
            while(indice > inf) {
                log->comparacoes++;
                if (arr[indice] < arr[indice - 1]) {
                    swap(arr + indice, arr + (indice - 1));
                    swapped = true;
                    log->trocas++;
                }
                indice--;
            }
            inf++;

        } else {
            indice = 0;
            while(indice < sup) {
                log->comparacoes++;
                if (arr[indice] > arr[indice + 1]) {
                    swap(arr + indice, arr + (indice + 1));
                    swapped = true;
                    log->trocas++;
                }
                indice++;
            }
            sup--;
        }
        reverse = !reverse;

    } while(swapped);

}

