#include "stdio.h"
#include "minunit.h"
#include "priority_queue.h"

int tests_run = 0;

compare dummy_func = (void *)0xDEADBEEF;

static int int_min_cmp(const void *obj1, const void *obj2)
{
    int val1 = *((int *)obj1);
    int val2 = *((int *)obj2);

    if (val1 > val2) {
        return 2;
    } 
    
    if (val1 < val2) {
        return 1;
    }

    return 0;
}

static int int_max_cmp(const void *obj1, const void *obj2)
{
    int val1 = *((int *)obj1);
    int val2 = *((int *)obj2);

    if (val1 > val2) {
        return 1;
    } 
    if (val1 < val2) {
        return 2;
    } 
    
    return 0;
}

static char *pq_max_test()
{    
    int i;
    int test_data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct pq *queue = pq_create(int_max_cmp);

    for (i = 0; i < 10; i++) {
        pq_insert(queue, &test_data[i]);
    }

    for (i = 0; i < 10; i++) {
        int val = *((int *)pq_remove(queue));
        mu_assert("values removed out of order\n", val == test_data[9 - i]);
    }

    pq_destroy(queue);

    return 0;
}

static char *pq_min_test()
{
    int i;
    int test_data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct pq *queue = pq_create(int_min_cmp);

    for (i = 0; i < 10; i++) {
        pq_insert(queue, &test_data[i]);
    }

    for (i = 0; i < 10; i++) {
        int val = *((int *)pq_remove(queue));
        mu_assert("values removed out of order\n", val == test_data[i]);
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
    mu_run_test(pq_min_test);
    mu_run_test(pq_max_test);
    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();

    if (result != 0) {
        printf("%s", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run %d\n", tests_run);

    return result != 0;
}
