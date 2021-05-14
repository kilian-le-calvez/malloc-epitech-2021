/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_calloc_reallocarray
*/


#include <criterion/criterion.h>
#include <dlfcn.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str);

Test(calloc_reallocarray, call)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mcalloc)(size_t mmemb, size_t size) = dlsym(handle, "calloc");
    void *(*mreallocarray)(void *ptr, size_t mmemb, size_t size) =
    dlsym(handle, "reallocarray");

    char *str = mcalloc(11, 1);
    fill_str('A', 10, &str);
    cr_assert_str_eq(str, "AAAAAAAAAA");
    str = mreallocarray(str, 20, 1);
    cr_assert_str_eq(str, "AAAAAAAAAA");
}