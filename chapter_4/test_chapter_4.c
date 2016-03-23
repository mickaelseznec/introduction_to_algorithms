#include "unity.h"
#include "chapter_4.h"

#define ARRAY_SIZE      17

static int array[ARRAY_SIZE] = {
    13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

void test_max_subarray() {
    struct subarray_res result = max_subarray(array, ARRAY_SIZE);
    TEST_ASSERT_EQUAL_INT(7, result.from);
    TEST_ASSERT_EQUAL_INT(10, result.to);
    TEST_ASSERT_EQUAL_INT(43, result.sum);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_max_subarray);
    return UNITY_END();
}
