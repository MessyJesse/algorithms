#include <stdlib.h>
#include "stack.h"
#include "vector.h"
#include "vector_def.h"

struct stack {
    struct vector vec;
    size_t index;
};

struct stack *stack_create(size_t size)
{
    struct stack *stack;

    stack = calloc(1, sizeof(*stack));
    
    if (!stack)
        return NULL;
            
    stack->vec.size = size;
    vector_resize(&stack->vec, 1);

    return stack;
}

//TODO: Do we care that this can fail?
void stack_push(struct stack *stack, void *elem)
{
    if (!stack || !elem)
        return;

    if (stack->index == stack->vec.len) {
        vector_resize(&stack->vec, stack->index * 2);
    }

    vector_set(&stack->vec, stack->index, elem);
    stack->index++;
}

void *stack_pop(struct stack *stack)
{
    if (!stack)
        return NULL;

    --stack->index;
    return vector_get(&stack->vec, stack->index); 
}
