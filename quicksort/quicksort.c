#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

struct array {
    void *base;
    int obj_count;
    size_t obj_size;
    compare_func compare;
    void *swap;
};

static void array_swap(struct array *array, int index1, int index2)
{   
    void *obj1 = (void *)((uintptr_t)array->base + (index1 * array->obj_size));
    void *obj2 = (void *)((uintptr_t)array->base + (index2 * array->obj_size));

    memcpy(array->swap, obj1, array->obj_size);
    memcpy(obj1, obj2, array->obj_size);
    memcpy(obj2, array->swap, array->obj_size);
}

static int array_compare_index(struct array *array, int index1,
                                      int index2)
{
    void *obj1 = (void *)((uintptr_t)array->base + (index1 * array->obj_size));
    void *obj2 = (void *)((uintptr_t)array->base + (index2 * array->obj_size));

    return array->compare(obj1, obj2);
}

static int array_partition(struct array *array, int start, int end)
{
    int i;
    int pivot;
    int firsthigh;

    pivot = end; 
    firsthigh = start;

    for (i = start; i < end; i++) {
        int order = array_compare_index(array, pivot, i);
        if (order == 1) {
            array_swap(array, i, firsthigh);
            firsthigh++;
        }
    }

    array_swap(array, pivot, firsthigh);

    return firsthigh;
}

static void array_quicksort(struct array *array, int start, 
                            int end)
{
    int partition; 

    if ((end - start) > 0) {
        partition = array_partition(array, start, end);
        array_quicksort(array, start, partition - 1);
        array_quicksort(array, partition + 1, end);
    }
}

void quicksort(void *base, int obj_count, size_t obj_size,
               compare_func compare)
{
    struct array array;

    array.base = base;
    array.obj_count = obj_count;
    array.obj_size = obj_size;
    array.compare = compare;
    array.swap = malloc(obj_size);

    array_quicksort(&array, 0, obj_count - 1);
}
