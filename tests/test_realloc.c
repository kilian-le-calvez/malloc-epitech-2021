/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_realloc
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include <time.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str)
{
    int i;

    for (i = 0; i < size; i++)
        (*str)[i] = c;
    (*str)[i] = '\0';
}

Test(realloc_test, test01)
{
    time_t t;
    srand((unsigned) time(&t));
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void *(*mrealloc)(void *ptr, size_t size) = dlsym(handle, "realloc");
    size_t size = 10;
    char *ptr = mmalloc(size);

    fill_str('A', size, &ptr);
    ptr = mrealloc(ptr, size);
    cr_assert_str_eq(ptr, "AAAAAAAAAA");
}

Test(realloc_test, test02)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void *(*mrealloc)(void *ptr, size_t size) = dlsym(handle, "realloc");
    void (*mfree)(void *ptr) = dlsym(handle, "free");
    size_t size = 10;
    char *ptr = mmalloc(size);
    char *ptr2 = mmalloc(size + 10);
    char *ptr3 = mmalloc(size);

    mfree(ptr2);
    ptr = mrealloc(ptr, size * 2);
}