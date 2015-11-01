#include <stddef.h>

#define HIGH_PRIORITY 1
#define LOW_PRIORITY 0
#define EQUAL_PRIORITY -1

typedef int (*compare)(const void *, const void *);

struct pq *pq_create(compare compare_func);
void pq_destroy(struct pq *queue);
int pq_insert(struct pq *queue, void *obj);
void *pq_remove(struct pq *queue);

