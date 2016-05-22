#pragma once

#include <stdlib.h>

struct hashmap_chain {
    struct hashmap_chain *prev;
    struct hashmap_chain *next;
    int value;
    char key[];
};

struct hashmap {
    size_t size;
    struct hashmap_chain *hashmap_array[];
};

struct hashmap *hashmap_create(size_t size);
int hashmap_destroy(struct hashmap *hashmap);

int hashmap_add(struct hashmap *hashmap, char *key, int value);
int hashmap_get(struct hashmap *hashmap, char *key, int *ret);
int hashmap_delete(struct hashmap *hashmap, char *key);
