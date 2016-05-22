#pragma once

#include <stdlib.h>

#define REQUIRE_NOT_NULL(arg, ret)                  \
    do {                                            \
        if ((arg) == NULL) {                        \
            return (ret);                           \
        }                                           \
    } while(0)

#define print_array(array, size) _Generic((array)[0], int: print_array_int)((array), (size))
#define shuffle_array(array, size) _Generic((array)[0], int: shuffle_array_int)((array), (size))
#define swap(array, n, m) _Generic((array)[0], int: swap_int)((array), (n), (m))

#define MAKE_TEST_SORT_TYPE(type)                                       \
    void test_##type##_sort() {                                         \
        int *result = type##_sort(unsorted_array, ARRAY_SIZE);          \
        TEST_ASSERT_EQUAL_INT_ARRAY(sorted_array, result, ARRAY_SIZE);  \
        free(result);                                                   \
    }

void print_array_int(int *arr, size_t len);
void shuffle_array_int(int *arr, size_t len);
void swap_int(int *arr, int n, int m);
