#include "../sortingutils.h"

int median_of_three(int a, int b, int  c) {

    if ((a <= b && a >= c) || (a >= b && a <= c)) {
        return a;
    } else if ((b <= a && b >= c) || (b >= a && b <= c)) {
        return b;
    } else {
        return c;
    }

}

void three_way_part(int *arr, int inf, int sup, int *lower, int *greater, struct log_info *log) {
    if (sup <= inf) {
        return;
    }

    // Calculating the pivot
    int delta_median = (sup - inf)/2;
    int median = arr[inf + delta_median];

    int pivot = median_of_three(median, arr[inf], arr[sup]);

    // Partitioning
    *lower = inf;
    *greater = sup;
    int i = inf;

    while (i <= *greater) {

        if (arr[i] < pivot) {
            log->comparacoes++;
            log->trocas++;
            swap(arr + (*lower), arr + i);
            (*lower)++;
            i++;
        } else if (arr[i] > pivot) {
            log->comparacoes++;
            log->comparacoes++;
            log->trocas++;
            swap(arr + (*greater), arr + i);
            (*greater)--;
        } else {
            i++;
        }
    }

}

void rec_quicksort(int *arr, int inf, int sup, struct log_info* log) {
    int lower;
    int upper;
    if (sup > inf){
        three_way_part(arr, inf, sup, &lower, &upper, log);

        rec_quicksort(arr, inf, lower - 1, log);
        rec_quicksort(arr, upper + 1, sup, log);
	}
}

void better_quicksort(int *arr, int arr_size, struct log_info* log) {
    log->trocas = 0;
    log->comparacoes = 0;
    rec_quicksort(arr, 0, arr_size - 1, log);
}

