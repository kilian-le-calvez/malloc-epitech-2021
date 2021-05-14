/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_building
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str);

Test(building, realloc_error)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mrealloc)(void *ptr, size_t size) =
    dlsym(handle, "realloc");
    char *ptr;

    ptr = mrealloc(NULL, 500);
    fill_str('A', 10, &ptr);
    cr_assert_str_eq(ptr, "AAAAAAAAAA");
    ptr = mrealloc(ptr, 0);
    cr_assert_eq(ptr, NULL);
}