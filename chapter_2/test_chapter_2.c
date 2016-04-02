#include "unity.h"
#include "utils.h"
#include "chapter_2.h"


#define ARRAY_SIZE      10

static int unsorted_array[ARRAY_SIZE] = {9, 3, 0, 8, 9, -1, -4, 4, 10, 3};
static int sorted_array[ARRAY_SIZE] = {-4, -1, 0, 3, 3, 4, 8, 9, 9, 10};

#define MAKE_TEST_SORT_TYPE(type)                                       \
    void test_##type##_sort() {                                         \
        int *result = type##_sort(unsorted_array, ARRAY_SIZE);          \
        TEST_ASSERT_EQUAL_INT_ARRAY(sorted_array, result, ARRAY_SIZE);  \
        free(result);                                                   \
    }

MAKE_TEST_SORT_TYPE(insertion)
MAKE_TEST_SORT_TYPE(bubble)
MAKE_TEST_SORT_TYPE(merge)

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_insertion_sort);
    RUN_TEST(test_bubble_sort);
    RUN_TEST(test_merge_sort);
    print_array(sorted_array, ARRAY_SIZE);
    return UNITY_END();
}
