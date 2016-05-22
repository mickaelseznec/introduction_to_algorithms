#include "unity.h"
#include "utils.h"
#include "chapter_10.h"

void test_hashmap_10() {
    char *one = "one";
    char *two = "two";
    char *three = "three";
    char *four = "four";
    char *five = "five";

    int ret = 0;

    struct hashmap *hashmap = hashmap_create(10);
    TEST_ASSERT_NOT_NULL(hashmap);

    TEST_ASSERT_EQUAL_INT(0, hashmap_add(hashmap, one, 1));
    TEST_ASSERT_EQUAL_INT(0, hashmap_add(hashmap, two, 2));
    TEST_ASSERT_EQUAL_INT(0, hashmap_add(hashmap, three, 3));
    TEST_ASSERT_EQUAL_INT(0, hashmap_add(hashmap, four, 4));

    TEST_ASSERT_EQUAL_INT(0, hashmap_get(hashmap, one, &ret));
    TEST_ASSERT_EQUAL_INT(1, ret);

    TEST_ASSERT_EQUAL_INT(0, hashmap_get(hashmap, two, &ret));
    TEST_ASSERT_EQUAL_INT(2, ret);

    TEST_ASSERT_EQUAL_INT(0, hashmap_get(hashmap, three, &ret));
    TEST_ASSERT_EQUAL_INT(3, ret);

    TEST_ASSERT_EQUAL_INT(0, hashmap_get(hashmap, four, &ret));
    TEST_ASSERT_EQUAL_INT(4, ret);

    TEST_ASSERT_EQUAL_INT(-1, hashmap_get(hashmap, five, &ret));

    TEST_ASSERT_EQUAL_INT(hashmap_delete(hashmap, one), 0);

    TEST_ASSERT_EQUAL_INT(-1, hashmap_get(hashmap, one, &ret));

    TEST_ASSERT_EQUAL_INT(hashmap_destroy(hashmap), 0);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_hashmap_10);
    return UNITY_END();
}
