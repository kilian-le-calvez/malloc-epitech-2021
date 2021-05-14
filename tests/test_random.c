/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_random
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include <time.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str);

Test(random_test, test01)
{
    time_t t;
    srand((unsigned) time(&t));

    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    char *ptr;
    size_t size;
    int loop = rand () % 150;

    for (int i = 0; i < loop; i++) {
        size = 615;
        ptr = malloc(size);
        fill_str((rand() % 90 + 65), size, &ptr);
        if (i % 3 == 0)
            free(ptr);
    }
    cr_assert_eq(true, true);
}

Test(random_test, MANYMALLOC)
{
    time_t t;
    srand((unsigned) time(&t));

    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void (*my_putnbr)(size_t size) = dlsym(handle, "my_putnbr");
    void (*my_putstr)(char *str) = dlsym(handle, "my_putstr");
    char *ptr;
    size_t size;
    int loop = rand () % 500 + 1;

    for (int i = 0; i < loop; i++) {
        size = 160;
        ptr = mmalloc(size);
    }
    cr_assert_eq(true, true);
}
