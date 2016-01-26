typedef int (*compare_func)(const void *, const void*);
void heap_sort(void *base, unsigned int num_elem, size_t size_elem,
               compare_func comp);
