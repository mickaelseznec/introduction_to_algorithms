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
        swap_int(new_arr, i, ind_min);
    }

    return new_arr;
}

int *bubble_sort(int *arr, size_t len) {
    int *new_arr = (int *) malloc(len * sizeof(int));
    memcpy(new_arr, arr, len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len - 1; j++) {
            if (new_arr[j] > new_arr[j + 1])
                swap_int(new_arr, j, j + 1);
        }
    }

    return new_arr;
}

void make_heap(int *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        for (int j = i; j > 0 && arr[j] > arr[(j - 1) / 2]; j = (j - 1) /2) {
            swap_int(arr, j, (j - 1) / 2);
        }
    }
}

int *heap_sort(int *arr, size_t len) {
    int *heap = (int *) malloc(len * sizeof(int));
    int *new_arr = (int *) malloc(len * sizeof(int));
    memcpy(heap, arr, len * sizeof(int));
    make_heap(heap, len);
    for (size_t i = 0; i < len; i++) {
        new_arr[len - 1 - i] = heap[0];
        heap[0] = INT_MIN;

        size_t j = 0;
        while(2 * j + 1 < len) {
            if (2 * j + 2 == len) {
                swap_int(heap, j, 2 * j + 1);
                j = 2 * j + 1;
            } else {
                if (heap[2 * j + 1] > heap[2 * j + 2]) {
                    swap_int(heap, j, 2 * j + 1);
                    j = 2 * j + 1;
                } else {
                    swap_int(heap, j, 2 * j + 2);
                    j = 2 * j + 2;
                }
            }
        }
    }
    free(heap);
    return new_arr;
}

int *_merge_sort(int *arr, size_t len) {
    if (len < 2)
        return arr;
    if (len == 2) {
        if (arr[0] > arr[1])
            swap_int(arr, 0, 1);
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
