#include <stdlib.h>
#include <string.h>

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

