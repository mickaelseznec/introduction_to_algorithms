#include "unity.h"
#include "utils.h"
#include "chapter_7.h"


#define ARRAY_SIZE      10

static int unsorted_array[ARRAY_SIZE] = {9, 3, 0, 8, 9, -1, -4, 4, 10, 3};
static int sorted_array[ARRAY_SIZE] = {-4, -1, 0, 3, 3, 4, 8, 9, 9, 10};

MAKE_TEST_SORT_TYPE(quick)

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_quick_sort);
    return UNITY_END();
}
