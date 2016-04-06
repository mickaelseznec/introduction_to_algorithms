#include <stdlib.h>
#include <string.h>

#include "utils.h"

static size_t _quick_sort_partition(int *arr, size_t len) {
    int pivot = arr[len - 1];
    size_t low = 0;
    for (size_t i = 0; i < len - 1; i++) {
        if (arr[i] <= pivot) {
            swap(arr, i, low);
            low++;
        }
    }
    swap(arr, len - 1, low);
    return low;
}

static void _quick_sort(int *arr, size_t len) {
    if (len < 1)
        return;
    size_t q = _quick_sort_partition(arr, len);
    _quick_sort(arr, q);
    _quick_sort(arr + q + 1, len - (q + 1));
}

int *quick_sort(int *arr, size_t len) {
    int *result = (int *) malloc(len * sizeof(int));
    memcpy(result, arr, len * sizeof(int));
    _quick_sort(result, len);
    return result;
}

