#include <stddef.h>

typedef int (*compare_func)(const void *, const void*);
void quicksort(void *base, int obj_count, size_t obj_size,
               compare_func comp);
