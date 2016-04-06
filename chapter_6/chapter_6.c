#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "chapter_6.h"
#include "utils.h"

static void make_heap(int *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        for (int j = i; j > 0 && arr[j] > arr[(j - 1) / 2]; j = (j - 1) /2) {
            swap(arr, j, (j - 1) / 2);
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
                swap(heap, j, 2 * j + 1);
                j = 2 * j + 1;
            } else {
                if (heap[2 * j + 1] > heap[2 * j + 2]) {
                    swap(heap, j, 2 * j + 1);
                    j = 2 * j + 1;
                } else {
                    swap(heap, j, 2 * j + 2);
                    j = 2 * j + 2;
                }
            }
        }
    }
    free(heap);
    return new_arr;
}

