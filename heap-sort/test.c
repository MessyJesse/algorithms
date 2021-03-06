#include <stdio.h>
#include <minunit.h>
#include "heap_sort.h"

int tests_run = 0;

int max_comp(const void *obj1, const void *obj2)
{
    int val1 = *(int *)obj1;
    int val2 = *(int *)obj2;

    if (val1 > val2) {
        return 1;
    }

    if (val1 < val2) {
        return 2;
    }

    return 0;
}

int min_comp(const void *obj1, const void *obj2)
{
    int val1 = *(int *)obj1;
    int val2 = *(int *)obj2;

    if (val1 < val2) {
        return 1;
    }

    if (val1 > val2) {
        return 2;
    }

    return 0;
}

static char *test_min_heap_sort(void)
{
    int i;
    int previous;
    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 

    heap_sort(data, 10, sizeof(int), min_comp);
    previous = data[0];
    for (i = 1; i < 10; i++) {
        mu_assert("wrong order for min sort\n", data[i] < previous);
        previous = data[i];
    }

    return 0;
}

static char *test_max_heap_sort(void)
{
    int i;
    int previous;
    int data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; 

    heap_sort(data, 10, sizeof(int), max_comp);
    previous = data[0];
    for (i = 1; i < 10; i++) {
        mu_assert("wrong order for max sort\n", data[i] > previous);
        previous = data[i];
    }

    return 0;
}

static char *all_tests(void)
{
    mu_run_test(test_max_heap_sort);
    mu_run_test(test_min_heap_sort);
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
