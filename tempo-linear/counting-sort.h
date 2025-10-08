#include <stdlib.h>
#include <string.h>
#include "../sortingutils.h"

void countingsort(int *arr, int arr_size, struct log_info *log) {

    // Ensures no out-of-bounds access
    if (arr_size < 1) {
        return;
    }

    // Grab the greatest element in the original array
    int vector_greatest = arr[0];
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] > vector_greatest) {
            vector_greatest = arr[i];
        }
    }

    int *count_vector = (int *)calloc(vector_greatest + 1, sizeof(int));
    int *aux_vector = (int *)calloc(arr_size, sizeof(int));

    for (int i = 0; i < arr_size; i++) {
        count_vector[arr[i]]++;
    }

    for (int i = 1; i < vector_greatest + 1; i++) {
        count_vector[i] += count_vector[i - 1];
    }

    for (int i = arr_size - 1; i >= 0; i--) {
        aux_vector[count_vector[arr[i]] - 1] = arr[i];
        count_vector[arr[i]] = count_vector[arr[i]] - 1;
    }

    // This line would be unnecessary if the input vector was
    // heap allocated, but assuming it is not we need some
    // memcpy() overhead

    memcpy(arr, aux_vector, arr_size * sizeof(int));
    free(count_vector);
    free(aux_vector);

}
