#ifndef __VECTOR_DEF__
#define __VECTOR_DEF__

#include <stddef.h>

/**
 * Implementation of the vector ADT
 */
struct vector {
    size_t len;
    size_t size;
    void *arr;
};

#endif


