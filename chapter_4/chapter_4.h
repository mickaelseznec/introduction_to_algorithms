#ifndef __CHAPTER_2_H__
#define __CHAPTER_2_H__

#include <stdlib.h>

struct subarray_res {
    size_t  from;
    size_t  to;
    int     sum;
};

struct subarray_res max_subarray(int *array, size_t len);
void matrix_multiply_naive(size_t matrix_size,
        int matrix_c[matrix_size][matrix_size],
        int matrix_a[matrix_size][matrix_size],
        int matrix_b[matrix_size][matrix_size]);

#endif
