#include "stdlib.h"
#include "priority_queue.h"

struct pq {
    unsigned int num_obj;
    unsigned int max_num_obj;
    size_t size;
    void **queue;
    compare compare_obj;
};

static inline unsigned int heap_parent(unsigned int i)
{
    return i / 2;
}

static inline unsigned int heap_child(unsigned int i)
{
    return i * 2;
}

static void pq_bubble_down(struct pq *queue, unsigned int parent)
{
    int i;
    int order;
    unsigned int min_index = parent;
    unsigned int child = heap_child(parent);

    for (i =  0; i <=  1; i++) {
        if (child + i > queue->num_obj) {
            break;
        }

        order = queue->compare_obj(queue->queue[min_index], queue->queue[child + i]);
        if (order == 2) {
            min_index = child + i;
        }
    }
    
    if (min_index != parent) {
        void *min_obj = queue->queue[min_index];
        queue->queue[min_index] = queue->queue[parent];
        queue->queue[parent] = min_obj;
        pq_bubble_down(queue, min_index);
    }
}

static void pq_bubble_up(struct pq *queue, unsigned int child)
{
    int order;
    unsigned int parent = heap_parent(child);

    if (!parent) {
        return;
    }    

    order = queue->compare_obj(queue->queue[child], queue->queue[parent]);
    if (order == 1) {
        void *child_obj = queue->queue[child];
        queue->queue[child] = queue->queue[parent];
        queue->queue[parent] = child_obj;
        pq_bubble_up(queue, parent);
    }
}

struct pq *pq_create(compare compare_func)
{
    struct pq *queue;
    
    if (!compare_func) {
        return NULL;
    }

    queue = malloc(sizeof(*queue));
    if (!queue) {
        return NULL;
    }

    queue->queue = malloc(sizeof(void *));
    if (!queue->queue) {
        free(queue);
        return NULL;
    }

    queue->num_obj = 0;
    queue->size = sizeof(void *);
    queue->max_num_obj = 0;
    queue->compare_obj = compare_func;

    return queue;
}

void pq_destroy(struct pq *queue)
{
    if (queue) {
        free(queue->queue);
        free(queue);
    }
}

int pq_insert(struct pq *queue, void *obj)
{

    if (!queue) {
        return -1;
    }

    if (queue->num_obj == queue->max_num_obj) {
        void **new_queue = realloc(queue->queue, queue->size * 2);

        if (!new_queue) {
            return -1;
        }
        
        queue->size = queue->size * 2;
        queue->queue = new_queue;
        //The first element in the heap is at index 1 in the array
        queue->max_num_obj = queue->size / sizeof(void *) - 1;
    }

    queue->num_obj++;
    queue->queue[queue->num_obj] = obj;
    pq_bubble_up(queue, queue->num_obj);

    return 0;
}

void *pq_remove(struct pq *queue)
{
    void *ret;

    if (!queue) {
        return NULL;
    }

    if (queue->num_obj == 0) {
        return NULL;
    }

    ret = queue->queue[1]; 
    queue->queue[1] = queue->queue[queue->num_obj];
    queue->num_obj--;
    pq_bubble_down(queue, 1);

    return ret;
}

