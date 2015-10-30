#include "stdio.h"
#include "minunit.h"
#include "priority_queue.h"

int tests_run = 0;

compare dummy_func = (void *)0xDEADBEEF;

static int int_min_cmp(const void *obj1, const void *obj2)
{

}

static int int_max_cmp(const void *obj1, const void *obj2)
{

}

static char *pq_insert_test()
{
    char test_data[10];
    int i;
    struct pq *queue = pq_create(dummy_func);

    for (i = 0; i < 10; i++) {
        pq_insert(queue, &test_data[i]);
    }

    pq_destroy(queue);

    return 0;
}

static char *pq_create_test()
{
    struct pq *queue = pq_create(dummy_func);
    mu_assert("pq_create return NULL pointer", queue != NULL);
    pq_destroy(queue);

    queue = pq_create(NULL);
    mu_assert("pq_return non-NULL on invalid input: NULL func", queue == NULL);
    pq_destroy(queue);

    return 0;
}

static char *all_tests() 
{
    mu_run_test(pq_create_test);
    mu_run_test(pq_insert_test);
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
