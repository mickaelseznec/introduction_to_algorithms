#include <stdio.h>
#include <bsd/stdlib.h>

void print_array_int(int *arr, size_t len) {
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

void shuffle_array_int(int *arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        swap_int(arr, i, i + arc4random_uniform(len - i));
    }
}
