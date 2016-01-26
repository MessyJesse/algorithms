#ifndef __VECTOR__
#define __VECTOR__

#include <stddef.h>

/**
 * Functions return NULL or (int)(-1) on error.
 */
struct vector;

/**
 * vector_create(len, size):
 * Allocates, intializes and returns a new vector of $len elements with bounds 0
 * through $len - 1, unless $len is 0, in which case the array has no elements.
 * Each element occupies $size bytes. The bytes in each element are intialized
 * to 0. $size must include any padding that may be required for alignment so
 * that the actual array can be created by allocating $len * $size bytes.
 */
struct vector *vector_create(size_t len, size_t size);

/**
 * vector_destroy(vec):
 * Deallocates and clears $vec. 
 */
void vector_destroy(struct vector *vec);

/**
 * vector_length(vec):
 * Returns the number of elements in $vec.
 */
size_t vector_length(const struct vector *vec);

/**
 * vector_get(vec, i):
 * Returns a pointer to element $i; it's analogous to &a[i] when a is a declared
 * C array. Clients access the value of the element by dereferencing the pointer
 * returned by vector_get.
 */
void *vector_get(const struct vector *vec, size_t i);

/**
 * vector_set(vec, i, elem):
 * Overwrites the new element pointed to by $elem. Returns elem.
 */
void *vector_set(struct vector *vec, size_t i, const void *elem);

/**
 * vector_append(vec, elem):
 * Append $elem to $vec.
 * int vector_append(struct vector *vec, const void *elem);
 */

/**
 * vector_resize(vec, len):
 * Changes the size of vec so that it holds $len elements, expanding or
 * contracting it as necessary. If $len excceeds the current length of $vec, the
 * new elements are intialized to 0. Calling vector_resize invalidates any
 * values returned by previous calls vector_get.
 */
int vector_resize(struct vector *vec, size_t len);

/**
 * vector_copy(vec, len):
 * Returns a copy of $vec that holds the first $len of $vec. If $len exceeds the
 * number of elements in $vec, the excess elements in the copy are initialized
 * to 0.
 */
struct vector *vector_copy(const struct vector *vec, size_t len);

#undef __VECTOR__
#endif
