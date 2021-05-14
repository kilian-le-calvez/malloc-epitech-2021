/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_free
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str);

Test(free_basics, simple_free)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void (*mfree)(void *ptr) = dlsym(handle, "free");

    char *str = mmalloc(11);
    fill_str('A', 10, &str);
    cr_assert_str_eq(str, "AAAAAAAAAA");
    mfree(str);
    str = mmalloc(21);
    fill_str('A', 20, &str);
    cr_assert_str_eq(str, "AAAAAAAAAAAAAAAAAAAA");
}

Test(free_basics, other_free)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void (*mfree)(void *ptr) = dlsym(handle, "free");

    char *str1 = mmalloc(11);
    char *str2 = mmalloc(11);
    char *str3 = mmalloc(11);
    char *str4 = mmalloc(11);

    mfree(str2);
    mfree(str1);
    mfree(str3);
    mfree(str4);
}