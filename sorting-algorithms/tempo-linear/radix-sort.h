#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sortingutils.h"

int get_digit(int num, int exp) {
    return (num / exp) % 10;
}

void radix_msd_rec(int *arr, int arr_size, int exp) {
    if (arr_size <= 1 || exp == 0) return;

    int *output = (int*) calloc(arr_size, sizeof(int)); 
    int count[10] = {0};

    for (int i = 0; i < arr_size; i++)
        count[get_digit(arr[i], exp)]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = arr_size - 1; i >= 0; i--) {
        int d = get_digit(arr[i], exp);
        output[count[d] - 1] = arr[i];
        count[d]--;
    }

    // Copy back
    memcpy(arr, output, arr_size * sizeof(int));
    free(output);

    // Recursive calls
    int start = 0;
    for (int i = 0; i < 10; i++) {
        int size = (i == 0 ? count[0] : count[i] - count[i - 1]);
        if (size > 1)
            radix_msd_rec(arr + start, size, exp / 10);
        start += size;
    }
}

void radixsort_msd(int *arr, int arr_size, struct log_info *log_info) {
    int max = arr[0];
    for (int i = 1; i < arr_size; i++)
        if (arr[i] > max)
            max = arr[i];

    int exp = 1;
    while (max / exp >= 10)
        exp *= 10;

    radix_msd_rec(arr, arr_size, exp);
}

void radixsort_lsd(int *arr, int n, struct log_info *log_info) {

    // Find maximum number
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int *output = (int*) calloc(n, sizeof(int));
        int count[10] = {0};

        for (int i = 0; i < n; i++)
            count[get_digit(arr[i], exp)]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int d = get_digit(arr[i], exp);
            output[count[d] - 1] = arr[i];
            count[d]--;
        }

        // Copy back to arr (Again memcpy overhead)
        memcpy(arr, output, n * sizeof(int));
        free(output);
    }
}
