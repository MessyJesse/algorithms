#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "minunit.h"
#include "stack.h"
#include "vector.h"

int tests_run = 0;

static char *test_stack_push_pop(void)
{
    struct stack *stack;
    int i;
    int *data;

    stack = stack_create(sizeof(int));

    for (i = 0; i < 10; i++) {
        stack_push(stack, &i);
    }

    for (i = 0; i < 10; i++) {
        data = stack_pop(stack);
        mu_assert("pop did not match push\n", *data == (9 - i));
    }


    data = stack_pop(stack);
    mu_assert("stack_pop did not return NULL on empty after push/pop\n", data == NULL);
    return 0;
}

static char *test_stack_pop(void)
{
    struct stack *stack;
    void *data;

    mu_assert("stack_pop returned non-NULL on NULL\n", stack_pop(NULL) == NULL);

    stack = stack_create(sizeof(int));
    data = stack_pop(stack);
    mu_assert("stack_pop did not return NULL on empty\n", data == NULL);
    return 0;
}

static char *test_stack_create(void)
{
    struct stack *stack;
    stack = stack_create(sizeof(int));
    mu_assert("stack_create returned a NULL pointer\n", stack != NULL);
    return 0;
}

static char *test_vector_resize(void)
{
    {
        int err; 
        
        //Verify that vector_resize returns 0 on NULL vec object
        err = vector_resize(NULL, 10);
        mu_assert("vector_resize returns positive on NULL vec\n", err == -1);
    }

    {
        struct vector *vec;
        int err; 
        
        //Verify vector_resize detects overflow   
        vec = vector_create(10, sizeof(int));
        err = vector_resize(vec, SIZE_MAX);
        mu_assert("vector_resize returns no error on invalid size\n", err == -1);
        err = vector_resize(vec, 20);
        mu_assert("vector_resize returns non-0 on valid size\n", err == 0);
        vector_destroy(vec);
    }

    {
        struct vector *vec;
        int err; 
        size_t size;
        int i;
        
        vec = vector_create(10, sizeof(int));
        err = vector_resize(vec, 100);
        mu_assert("vector_resize returns error on growing\n", err == 0);

        //Verify length is correct after growing with vector_resize    
        size = vector_length(vec);
        mu_assert("wrong vector length reported\n", size == 100);

        //Verify the vector is initialized to 0 after resize
        for (i = 0; i < 100; i++) {
            int *j = vector_get(vec, i);
            mu_assert("resized vector not initialized to zero\n", *j == 0);
        }

        vector_destroy(vec);
    }

    {
        struct vector *vec;
        int err; 
        size_t size;
        
        vec = vector_create(100, sizeof(int));
        
        err = vector_resize(vec, 10);
        mu_assert("vector_resize returns error on shrinking\n", err == 0);
        
        //Verify length is correct after shrinking with vector_resize    
        size = vector_length(vec);
        mu_assert("wrong vector length reported\n", size == 10);
        vector_destroy(vec);
    }

    {
        /**
         * Fill up the vector with data and verify it is still there after
         * growing the vector
         */
        struct vector *vec;
        int i;

        vec = vector_create(10, sizeof(int));

        for (i = 0; i < 10; i++) {
            vector_set(vec, i, &i); 
        }

        vector_resize(vec, 100);

        for (i = 0; i < 10; i++) {
            int *j = vector_get(vec, i);
            mu_assert("vector contents not copied after resize\n", *j == i);
        }
    }

    {
        /**
         * Fill up the vector with data and verify it is still there after
         * shrinking the vector
         */
        struct vector *vec;
        int i;

        vec = vector_create(100, sizeof(int));

        for (i = 0; i < 100; i++) {
            vector_set(vec, i, &i); 
        }

        vector_resize(vec, 10);

        for (i = 0; i < 10; i++) {
            int *j = vector_get(vec, i);
            mu_assert("vector contents not copied after resize\n", *j == i);
        }
    }
   
    return 0;
}

static char *test_vector_length(void)
{
    struct vector *vec;
    size_t len;

    //Verify vector_length returns 0 on NULL vector
    len = vector_length(NULL);
    mu_assert("vector_length return non-0 on NULL input\n", len ==0);
    vec = vector_create(10, sizeof(int)); 
    //Verify vector_lenght returns correct size at init
    len = vector_length(vec);
    mu_assert("vector_length returns incorrect value after intialization\n", len == 10);
    vector_destroy(vec);
    
    return 0;
}

static char *test_vector_set_and_get(void)
{
    {//Verify that the values we set in vector are the values we get back
        struct vector *vec;
        int i;
        int *j;
        
        vec = vector_create(10, sizeof(int));

        for (i = 0; i < 10; i++) {
            vector_set(vec, i, &i);
        }

        for (i = 0; i < 1; i++) {
            j = vector_get(vec, i);
            mu_assert("vector_get did not return what we set\n", *j == i * 0x5555);
        }

        vector_destroy(vec);
    }

    return 0;
}

static char *test_vector_init(void)
{
    struct vector *vec;
    int i;
    int *j;

    vec = vector_create(10, sizeof(int));

    for (i = 0; i < 10; i++) {
        j = vector_get(vec, i);
        mu_assert("vector_get returns non-0 value after init\n", *j == 0);
    }

    return 0;
}

static char *test_vector_set(void)
{
    {
        void *elem;

        elem = vector_set(NULL, 0, (void *)0xDEADBEEF);
        mu_assert("vector_set should return NULL on NULL\n", elem == NULL);
    }
       
    {
        struct vector *vec;
        void *elem;

        vec = vector_create(0, sizeof(int));
        elem = vector_set(vec, 0, (void *)0xDEADBEEF); 
        mu_assert("vector_set should return NULL on out of bounds access\n", elem == NULL);
        elem = vector_set(vec, 1, (void *)0xDEADBEEF); 
        mu_assert("vector_set should return NULL on out of bounds access\n", elem == NULL);
        vector_destroy(vec);
    }

    {
        struct vector *vec;
        void *elem;
        int i = 1;

        vec = vector_create(1, sizeof(int));
        elem = vector_set(vec, 0, NULL);
        mu_assert("vector_set should return NULL on NULL elem\n", elem == NULL);

        elem = vector_set(vec, 1, (void *)0xDEADBEEF);
        mu_assert("vector_set should return NULL on out of bounds access\n", elem == NULL);

        elem = vector_set(vec, 0, &i);
        mu_assert("vector_set should return the element that was set\n", *(int *)elem == i);

        vector_destroy(vec);
    }

    return 0;
}

static char *test_vector_get(void)
{
    {
        void *elem;

        elem = vector_get(NULL, 0);
        mu_assert("vector_get should return NULL on NULL", elem == NULL);
    }

    {
        struct vector *vec;
        void *elem;

        vec = vector_create(0, sizeof(int));
        elem = vector_get(vec, 0); 
        mu_assert("vector_get should return NULL on out of bounds access\n", elem == NULL);
        elem = vector_get(vec, 1); 
        mu_assert("vector_get should return NULL on out of bounds access\n", elem == NULL);

        vector_destroy(vec);
    }

    { 
        struct vector *vec;
        void *elem;

        vec = vector_create(1, sizeof(int));
        elem = vector_get(vec, 0); 
        mu_assert("vector_get should return non-NULL on in bounds access\n", elem != NULL);
        elem = vector_get(vec, 1); 
        mu_assert("vector_get should return NULL on out of bounds access\n", elem == NULL);
        vector_destroy(vec);
    }
   
    return 0; 
}

static char *test_vector_create(void)
{
    struct vector *vec;

    vec = vector_create(10, 0);
    mu_assert("vector_create returned non-NULL on invalid input\n", 
              vec == NULL);

    vec = vector_create(SIZE_MAX, SIZE_MAX);
    mu_assert("vector_create returned non-NULL on invalid input\n", 
              vec == NULL);

    vec = vector_create(0, 10);
    mu_assert("vector_create returned NULL on valid input\n", 
              vec != NULL);
    vector_destroy(vec);

    vec = vector_create(1, 10);
    mu_assert("vector_create returned NULL on valid input\n", 
              vec != NULL);
    vector_destroy(vec);

    return 0;
}

static char *all_tests(void)
{
    //vector tests
    mu_run_test(test_vector_create);
    mu_run_test(test_vector_get);
    mu_run_test(test_vector_set);
    mu_run_test(test_vector_init);
    mu_run_test(test_vector_set_and_get);
    mu_run_test(test_vector_length);
    mu_run_test(test_vector_resize);
    
    //stack tests
    mu_run_test(test_stack_create);
    mu_run_test(test_stack_pop);
    mu_run_test(test_stack_push_pop);

    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run %d\n", tests_run);

    return result != 0;
}
