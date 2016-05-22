#include <stdlib.h>
#include <string.h>

#include "chapter_10.h"
#include "utils.h"

static int naive_hash(char *string, size_t max) {
    int res = 1;
    for (size_t i = 0; string[i] != '\0'; i++) {
        res = (res * string[i]) % max;
    }
    return res;
}

static struct hashmap_chain *hashmap_chain_init(char *key, int value) {
    struct hashmap_chain *hashmap_chain = (struct hashmap_chain*) malloc(sizeof(*hashmap_chain) + sizeof(char) * (strlen(key) + 1));

    if (hashmap_chain == NULL)
        return NULL;

    strcpy(hashmap_chain->key, key);
    hashmap_chain->value = value;
    hashmap_chain->prev = NULL;
    hashmap_chain->next = NULL;

    return hashmap_chain;
}

static void hashmap_chain_push(struct hashmap_chain *hashmap_chain, char *key, int value) {
    if (key == NULL || hashmap_chain == NULL)
        return;

    struct hashmap_chain *next = hashmap_chain_init(key, value);

    if (next == NULL)
        return;

    while(hashmap_chain->next != NULL)
        hashmap_chain = hashmap_chain->next;

    next->prev = hashmap_chain;
    hashmap_chain->next = next;
}

static void hashmap_chain_destroy(struct hashmap_chain *hashmap_chain) {
    while (hashmap_chain != NULL) {
        struct hashmap_chain *next = hashmap_chain->next;
        free(hashmap_chain);
        hashmap_chain = next;
    }
}

struct hashmap *hashmap_create(size_t size) {
    struct hashmap *hashmap = (struct hashmap *) malloc(sizeof(struct hashmap_chain) + size * sizeof(struct hashmap_chain *));

    if (hashmap == NULL)
        return NULL;

    hashmap->size = size;
    for (size_t i = 0; i < size; i++)
        hashmap->hashmap_array[i] = NULL;

    return hashmap;
}

int hashmap_destroy(struct hashmap *hashmap) {
    REQUIRE_NOT_NULL(hashmap, -1);

    for (size_t i = 0; i < hashmap->size; i++)
        hashmap_chain_destroy(hashmap->hashmap_array[i]);

    free(hashmap);
    return 0;
}

int hashmap_add(struct hashmap *hashmap, char *key, int value) {
    REQUIRE_NOT_NULL(hashmap, -1);
    REQUIRE_NOT_NULL(key, -1);

    int index = naive_hash(key, hashmap->size);
    if (hashmap->hashmap_array[index] == NULL)
        hashmap->hashmap_array[index] = hashmap_chain_init(key, value);
    else
        hashmap_chain_push(hashmap->hashmap_array[index], key, value);
    return 0;
}

int hashmap_get(struct hashmap *hashmap, char *key, int *ret) {
    REQUIRE_NOT_NULL(hashmap, -1);
    REQUIRE_NOT_NULL(key, -1);

    int index = naive_hash(key, hashmap->size);
    struct hashmap_chain *hashmap_chain = hashmap->hashmap_array[index];

    while(hashmap_chain != NULL) {
        if (strcmp(hashmap_chain->key, key) == 0) {
            *ret = hashmap_chain->value;
            return 0;
        }
        hashmap_chain = hashmap_chain->next;
    }

    return -1;
}

int hashmap_delete(struct hashmap *hashmap, char *key) {
    REQUIRE_NOT_NULL(hashmap, -1);
    REQUIRE_NOT_NULL(key, -1);

    int index = naive_hash(key, hashmap->size);
    struct hashmap_chain *hashmap_chain = hashmap->hashmap_array[index];

    /* Special case as it is the first chain*/
    if (strcmp(hashmap_chain->key, key) == 0) {
        hashmap->hashmap_array[index] = hashmap_chain->next;
        if (hashmap_chain->next != NULL)
            hashmap_chain->next->prev = NULL;
        free(hashmap_chain);
        return 0;
    }
    hashmap_chain = hashmap_chain->next;
    while(hashmap_chain != NULL) {
        if (strcmp(hashmap_chain->key, key) == 0) {
            if (hashmap_chain->next != NULL)
                hashmap_chain->next->prev = hashmap_chain->prev;
            hashmap_chain->prev->next = hashmap_chain->next;
            free(hashmap_chain);
            return 0;
        }
        hashmap_chain = hashmap_chain->next;
    }

    return -1;
}
