#ifndef __CHAPTER_2_H__
#define __CHAPTER_2_H__

#include <stdlib.h>

struct subarray_res {
    size_t  from;
    size_t  to;
    int     sum;
};

struct subarray_res max_subarray(int *array, size_t len);

#endif
