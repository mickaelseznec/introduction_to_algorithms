#include "unity.h"
#include "utils.h"
#include "chapter_8.h"


#define ARRAY_SIZE      10

static int unsorted_array[ARRAY_SIZE] = {9, 3, 0, 8, 9, -1, -4, 4, 10, 3};
static int sorted_array[ARRAY_SIZE] = {-4, -1, 0, 3, 3, 4, 8, 9, 9, 10};

static float unsorted_float_array[ARRAY_SIZE] = {.78, .17, .39, .26, .72, .94, .21, .12, .23, .68};
static float sorted_float_array[ARRAY_SIZE]   = {.12, .17, .21, .23, .26, .39, .68, .72, .78, .94};

void test_bucket_sort() {
    float *result = bucket_sort(unsorted_float_array, ARRAY_SIZE);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted_float_array, result, ARRAY_SIZE);
    free(result);
}


MAKE_TEST_SORT_TYPE(counting)

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_counting_sort);
    RUN_TEST(test_bucket_sort);
    return UNITY_END();
}
