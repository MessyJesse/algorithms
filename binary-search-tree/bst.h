#include "stdint.h"

typedef struct bst_T bst;
typedef void (*proc_func)(void *);

void bst_insert(bst **root, uint32_t key, void *val);
void *bst_remove(bst **root, uint32_t key);
void *bst_lookup(bst *t, uint32_t key);
void *bst_min(bst *t);
void *bst_max(bst *t);
void bst_process(bst *t, proc_func f);

