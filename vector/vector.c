#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vector_def.h"

struct vector *vector_create(size_t len, size_t size)
{
    struct vector *vec;
    
    if (size == 0) 
        goto err0;

    vec = malloc(sizeof(*vec));
    if (!vec) 
        goto err0;

    vec->size = size;
    vec->len = len;
    vec->arr = calloc(len, size);

    if (!vec->arr) 
        goto err1;

    return vec;

err1:
    vector_destroy(vec);
err0:
    return NULL;
}

void vector_destroy(struct vector *vec)
{
    if (vec) {
        free(vec->arr);
        free(vec);
    }
}

size_t vector_length(const struct vector *vec)
{
    if (!vec)
        return 0;

    return vec->len;
}

void *vector_get(const struct vector *vec, size_t i)
{
    if (!vec) 
        return NULL;
    
    if (vec->len <= i)
        return NULL;

    return (void *)((uintptr_t)vec->arr + i * vec->size); 
}

void *vector_set(struct vector *vec, size_t i, const void *elem)
{
    if (!vec)
        return NULL;

    if (vec->len <= i)
        return NULL;

    if (!elem)
        return NULL;
    
    void *s1 = (void *)((uintptr_t)vec->arr + i * vec->size); 
    memcpy(s1, elem, vec->size); 

    return s1;
}


int vector_resize(struct vector *vec, size_t len)
{
    if (!vec)
        return -1;

    /* Check for overflow. */
    if (len > SIZE_MAX / vec->size) 
        return -1;

    void *new_arr = realloc(vec->arr, len * vec->size);

    if (!new_arr)
        return -1;

    /* Initialize the new memory to 0 */
    if (len > vec->len) {
        void *new_data = (void *)((uintptr_t)new_arr + vec->len * vec->size);
        memset(new_data, 0, len - vec->len);
    }

    vec->len = len;
    vec->arr = new_arr;

    return 0;
}


struct vector *vector_copy(const struct vector *vec, size_t len)
{
    struct vector *copy;

    if (!vec)
        return NULL;

    copy = vector_create(len, vec->size);

    if (!copy)
        return NULL;
    
    if (copy->len >= vec->len) {
        memcpy(copy->arr, vec->arr, vec->len * vec->size);
    } else {
        memcpy(copy->arr, vec->arr, copy->len * vec->size);
    }

    return copy;
}

