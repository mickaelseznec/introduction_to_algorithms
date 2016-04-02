#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "chapter_4.h"
#include "utils.h"

struct fll {
    struct fll *prev;
    float val;
    struct fll *next;
};

static void fll_clean(struct fll *ll) {
    struct fll *next;
    do {
        next = ll->next;
        free(ll);
        ll = next;
    } while(next != NULL);
}

static void fll_push(struct fll *ll, float val) {
    struct fll *pushed = (struct fll *) malloc(sizeof(struct fll));
    while (ll->next != NULL) {
        ll = ll->next;
    }
    ll->next = pushed;
    *pushed = (struct fll) {ll, val, NULL};
}

static void fll_remove(struct fll *ll) {
    if (ll->prev != NULL)
        ll->prev->next = ll->next;
    if (ll->next != NULL)
        ll->next->prev = ll->prev;
}

static void fll_prepend(struct fll *from, struct fll *new_ll) {
    if (from->prev != NULL)
        from->prev->next = new_ll;
    from->prev = new_ll;
    new_ll->next = from;
    new_ll->prev = from->prev;
}

float *bucket_sort(float *arr, size_t len) {
    struct fll **bucket =
        (struct fll **) calloc(len, sizeof(struct fll *));

    /* Put numbers in the right sub-bucket*/
    for (size_t i = 0; i < len; i++) {
        int index = (int) (arr[i] * len);
        if (bucket[index] != NULL) {
            fll_push(bucket[index], arr[i]);
        } else {
            bucket[index] = (struct fll *) malloc(sizeof(struct fll));
            *bucket[index] = (struct fll) {NULL, arr[i], NULL};
        }
    }

    /* Sort sub-buckets*/
    for (size_t i = 0; i < len; i++) {
        if (bucket[i] == NULL)
            continue;
        struct fll *ll = bucket[i];
        while (ll->next != NULL) {
            if (ll->val < ll->next->val) {
                ll = ll->next;
            } else {
                struct fll *misplaced = ll->next;
                fll_remove(ll->next);
                struct fll *lli;
                for (lli = bucket[i]; lli->val < misplaced->val; lli = lli->next) ;
                fll_prepend(lli, misplaced);
                if (lli == bucket[i])
                    bucket[i] = misplaced;
            }
        }
    }

    /* Concatenate ordered sub-buckets*/
    float *res = (float *) malloc(len * sizeof(float));
    for (size_t i = 0, j = 0; i < len; i++) {
        for (struct fll *ll = bucket[i]; ll != NULL; ll = ll->next) {
            res[j++] = ll->val;
        }
    }

    for (size_t i = 0; i < len; i++) {
        if (bucket[i] != NULL)
            fll_clean(bucket[i]);
    }
    free(bucket);
    return res;
}

static void find_minmax(int *arr, size_t len, int *min, int *max) {
    size_t i;
    if (len < 1)
        return;

    if (len % 2 == 0) {
        *max = (arr[0] > arr[1]) ? arr[0]: arr[1];
        *min = (arr[0] > arr[1]) ? arr[1]: arr[0];
        i = 2;
    } else {
        *max = arr[0];
        *min = arr[0];
        i = 1;
    }

    for (; i < len - 1; i += 2) {
        if (arr[i] > arr[i + 1]) {
            *max = (arr[i] > *max) ? arr[i]: *max;
            *min = (arr[i + 1] < *min) ? arr[i + 1]: *min;
        } else {
            *max = (arr[i + 1] > *max) ? arr[i + 1]: *max;
            *min = (arr[i] < *min) ? arr[i]: *min;
        }
    }
}

int *counting_sort(int *arr, size_t len) {
    int min, max;
    size_t range;

    find_minmax(arr, len, &min, &max);
    range = max - min + 1;

    int *count = (int *) calloc(range, sizeof(int));
    for (size_t i = 0; i < len; i++) {
        count[arr[i] - min]++;
    }
    for (size_t i = 1; i < range; i++) {
        count[i] += count[i -1];
    }

    int *res = (int *) malloc(len * sizeof(int));
    for (int i = len - 1; i >= 0; i--) {
        res[count[arr[i] - min]-- - 1] = arr[i];
    }

    free(count);
    return res;
}

static size_t _quick_sort_partition(int *arr, size_t len) {
    int pivot = arr[len - 1];
    size_t low = 0;
    for (size_t i = 0; i < len - 1; i++) {
        if (arr[i] <= pivot) {
            swap(arr, i, low);
            low++;
        }
    }
    swap(arr, len - 1, low);
    return low;
}

static void _quick_sort(int *arr, size_t len) {
    if (len < 1)
        return;
    size_t q = _quick_sort_partition(arr, len);
    _quick_sort(arr, q);
    _quick_sort(arr + q + 1, len - (q + 1));
}

int *quick_sort(int *arr, size_t len) {
    int *result = (int *) malloc(len * sizeof(int));
    memcpy(result, arr, len * sizeof(int));
    _quick_sort(result, len);
    return result;
}

static void make_heap(int *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        for (int j = i; j > 0 && arr[j] > arr[(j - 1) / 2]; j = (j - 1) /2) {
            swap(arr, j, (j - 1) / 2);
        }
    }
}

int *heap_sort(int *arr, size_t len) {
    int *heap = (int *) malloc(len * sizeof(int));
    int *new_arr = (int *) malloc(len * sizeof(int));
    memcpy(heap, arr, len * sizeof(int));
    make_heap(heap, len);
    for (size_t i = 0; i < len; i++) {
        new_arr[len - 1 - i] = heap[0];
        heap[0] = INT_MIN;

        size_t j = 0;
        while(2 * j + 1 < len) {
            if (2 * j + 2 == len) {
                swap(heap, j, 2 * j + 1);
                j = 2 * j + 1;
            } else {
                if (heap[2 * j + 1] > heap[2 * j + 2]) {
                    swap(heap, j, 2 * j + 1);
                    j = 2 * j + 1;
                } else {
                    swap(heap, j, 2 * j + 2);
                    j = 2 * j + 2;
                }
            }
        }
    }
    free(heap);
    return new_arr;
}


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
