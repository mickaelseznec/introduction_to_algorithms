#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "utils.h"

int *insertion_sort(int *arr, size_t len) {
    int ind_min;
    int *new_arr = (int *) malloc(len * sizeof(int));
    memcpy(new_arr, arr, len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        ind_min = i;
        for (size_t j = i + 1; j < len; j++) {
            if (new_arr[j] < new_arr[ind_min]) {
                ind_min = j;
            }
        }
        swap(new_arr, i, ind_min);
    }

    return new_arr;
}

int *bubble_sort(int *arr, size_t len) {
    int *new_arr = (int *) malloc(len * sizeof(int));
    memcpy(new_arr, arr, len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len - 1; j++) {
            if (new_arr[j] > new_arr[j + 1])
                swap(new_arr, j, j + 1);
        }
    }

    return new_arr;
}

int *_merge_sort(int *arr, size_t len) {
    if (len < 2)
        return arr;
    if (len == 2) {
        if (arr[0] > arr[1])
            swap(arr, 0, 1);
        return arr;
    }

    _merge_sort(arr, len / 2);
    _merge_sort(&arr[len / 2], (len + 1) / 2);

    size_t i = 0, n = 0, j = len / 2;
    int *new_arr = (int *) malloc(len * sizeof(int));
    while (i < len / 2 || j < len) {
        if (j >= len)
            new_arr[n++] = arr[i++];
        else if (i >= len / 2)
            new_arr[n++] = arr[j++];
        else if (arr[i] < arr[j])
            new_arr[n++] = arr[i++];
        else
            new_arr[n++] = arr[j++];
    }
    memcpy(arr, new_arr, len * sizeof(int));
    free(new_arr);

    return arr;
}

int *merge_sort(int *arr, size_t len) {
    int *new_arr = (int *) malloc(len * sizeof(int));
    memcpy(new_arr, arr, len * sizeof(int));
    return _merge_sort(new_arr, len);
}
