#include <stdio.h>

void print_int_array(int *arr, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[len - 1]);
}

void swap_int(int *arr, int n, int m) {
    int temp = arr[n];
    arr[n] = arr[m];
    arr[m] = temp;
}

