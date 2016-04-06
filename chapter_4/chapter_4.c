#include <stdlib.h>
#include <string.h>

#include "chapter_4.h"
#include "utils.h"

void matrix_multiply_naive(size_t matrix_size,
        int matrix_c[matrix_size][matrix_size],
        int matrix_a[matrix_size][matrix_size],
        int matrix_b[matrix_size][matrix_size]) {
    for (size_t i = 0; i < matrix_size; i++) {
        for (size_t j = 0; j < matrix_size; j++) {
            int cij = 0;
            for (size_t k = 0; k < matrix_size; k++) {
                cij += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_c[i][j] = cij;
        }
    }
}

static struct subarray_res middle_subarray(int *array, size_t len) {
    int *sums = (int *) malloc(len * sizeof(int));
    struct subarray_res res;

    size_t middle = len / 2;
    sums[middle] = array[middle];
    res = (struct subarray_res) {middle, middle, sums[middle]};
    int low_max = res.sum, high_max = res.sum;

    for (size_t i = middle + 1; i < len; i++) {
        sums[i] = sums[i - 1] + array[i];
    }
    for (int i = middle - 1; i >= 0; i--) {
        sums[i] = sums[i + 1] + array[i];
    }
    for (size_t i = 0; i <= middle; i++) {
        if (sums[i] > low_max) {
            res.from = i;
            low_max = sums[i];
        }
    }
    for (size_t i = middle; i < len; i++) {
        if (sums[i] > high_max) {
            res.to = i;
            high_max = sums[i];
        }
    }
    res.sum = high_max + low_max - res.sum;
    free(sums);
    return res;
}

struct subarray_res max_subarray(int *array, size_t len) {
    if (len < 2)
        return (struct subarray_res) {0, 0, array[0]};

    size_t middle = len / 2;
    struct subarray_res low = max_subarray(array, middle);
    struct subarray_res high = max_subarray(&array[middle], len - middle);
    struct subarray_res median = middle_subarray(array, len);

    if (low.sum > high.sum) {
        if (low.sum > median.sum) {
            return low;
        }
        return median;
    } else if (high.sum > median.sum) {
        high.from += middle;
        high.to += middle;
        return high;
    }
    return median;
}
