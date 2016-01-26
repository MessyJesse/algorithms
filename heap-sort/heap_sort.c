#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "heap_sort.h"

struct heap {
    void *base;
    void *swap;
    compare_func comp;
    unsigned int elem_count;
    size_t elem_size;
};

static inline void *obj_from_index(void *base, size_t size, unsigned int index)
{
    return (void *)((uintptr_t)base + ((index - 1) * size));
}

static inline int compare(compare_func comp, void *base, size_t size, 
                   unsigned int index1, unsigned int index2)
{
    void *obj1 = obj_from_index(base, size, index1);
    void *obj2 = obj_from_index(base, size, index2);

    return comp(obj1, obj2);
}

static void heap_swap(struct heap *heap, unsigned int index1, unsigned int index2)
{
    void *obj1, *obj2;

    obj1 = obj_from_index(heap->base, heap->elem_size, index1);
    obj2 = obj_from_index(heap->base, heap->elem_size, index2);

    memcpy(heap->swap, obj1, heap->elem_size);
    memcpy(obj1, obj2, heap->elem_size);
    memcpy(obj2, heap->swap, heap->elem_size);
}

static void heap_order(struct heap *heap, unsigned int index)
{
    int order;
    unsigned int largest = index;
    unsigned int left = index * 2; 
    unsigned int right = index * 2 + 1; 
    
    order = compare(heap->comp, heap->base, heap->elem_size, largest, left);
    if (left <= heap->elem_count && order == 2) {
        largest = left;
    }
    
    order = compare(heap->comp, heap->base, heap->elem_size, largest, right);
    if (right <= heap->elem_count && order == 2) {
        largest = right;
    }

    if (largest != index) {
        heap_swap(heap, largest, index);
        heap_order(heap, largest);
    }
}

static void heap_init(struct heap *heap, void *base, unsigned int elem_count, 
                      size_t elem_size, compare_func comp) 
{
    int i;

    heap->base = base;
    heap->comp = comp;
    heap->elem_count = elem_count;
    heap->elem_size = elem_size;
    heap->swap = malloc(elem_size);

    for (i = elem_count / 2; i > 0; i--) {
        heap_order(heap, i); 
    }
}

void heap_sort(void *base, unsigned int num_elem, size_t size_elem,
               compare_func comp)
{
    struct heap heap;
    unsigned int i;

    heap_init(&heap, base, num_elem, size_elem, comp);
    
    for (i = num_elem; i >= 2; i--) {
        heap_swap(&heap, 1, i);
        heap.elem_count -= 1;
        heap_order(&heap, 1);
    }
}

