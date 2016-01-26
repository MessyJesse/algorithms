#ifndef __STACK__
#define __STACK__

#include "vector_def.h"

struct stack *stack_create(size_t size);
void stack_push(struct stack *stack, void *);
void *stack_pop(struct stack *stack);

#endif
