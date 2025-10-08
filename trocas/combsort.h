#include <stdint.h>
#include "../sortingutils.h"

void combsort(int *arr, int arr_size, struct log_info *log) {

    double shrink_factor = 1.3;
    int32_t diff = (arr_size - 1)/2;

    bool swapped;

    // Bubblesorteia
    do {
        swapped = false;
        int32_t indice = 0;

        while(indice + diff < arr_size) {
            log->comparacoes++;

            if (arr[indice] > arr[indice + diff]) {
                swap(arr + indice, arr + indice + diff);
                swapped = true;
                log->trocas++;
            }

            indice++;
        }

        diff /= shrink_factor;
    } while(diff > 1 || swapped);

}

