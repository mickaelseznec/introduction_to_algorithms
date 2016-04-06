#include "unity.h"
#include "utils.h"
#include "chapter_4.h"

#define MAX_SUBARRAY_SIZE   17
#define ARRAY_SIZE          10
#define MATRIX_SIZE          4

static int array[MAX_SUBARRAY_SIZE] = {
    13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

static int matrix_a[MATRIX_SIZE][MATRIX_SIZE] = {
    {4, 1, 9, 5},
    {6, 3, 9, 4},
    {0, 8, 4, 9},
    {4, 7, 8, 1},
};

static int matrix_b[MATRIX_SIZE][MATRIX_SIZE] = {
    {8, 1, 1, 3},
    {3, 0, 1, 2},
    {0, 8, 0, 8},
    {9, 7, 1, 1},
};

static int matrix_result[MATRIX_SIZE][MATRIX_SIZE] = {
    { 80, 111, 10,  91},
    { 93, 106, 13, 100},
    {105,  95, 17,  57},
    { 62,  75, 12,  91},
};

static void test_max_subarray() {
    struct subarray_res result = max_subarray(array, MAX_SUBARRAY_SIZE);
    TEST_ASSERT_EQUAL_INT(7, result.from);
    TEST_ASSERT_EQUAL_INT(10, result.to);
    TEST_ASSERT_EQUAL_INT(43, result.sum);
}

static void test_matrix_naive() {
    int matrix_c[MATRIX_SIZE][MATRIX_SIZE];
    matrix_multiply_naive(MATRIX_SIZE, matrix_c, matrix_a, matrix_b);
    for (int i = 0; i < MATRIX_SIZE; i++)
        TEST_ASSERT_EQUAL_INT_ARRAY(matrix_result[i], matrix_c[i], MATRIX_SIZE);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_max_subarray);
    RUN_TEST(test_matrix_naive);
    return UNITY_END();
}
