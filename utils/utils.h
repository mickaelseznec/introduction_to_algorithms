#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>

#define print_array(array, size) _Generic((array)[0], int: print_array_int)((array), (size))
#define shuffle_array(array, size) _Generic((array)[0], int: shuffle_array_int)((array), (size))
#define swap(array, n, m) _Generic((array)[0], int: swap_int)((array), (n), (m))

void print_array_int(int *arr, size_t len);
void shuffle_array_int(int *arr, size_t len);
void swap_int(int *arr, int n, int m);

#endif
