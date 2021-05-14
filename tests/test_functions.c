/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_functions
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str);

Test(functions_limit, mextend_mem)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*extend_mem)(t_block **last, size_t size) =
    dlsym(handle, "extend_mem");

    if (extend_mem(NULL, 92233720368547758) == NULL)
        cr_assert_eq(true, true);
    else
        cr_assert_eq(true, false);
}

Test(functions_limit, mmalloc)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");

    if (mmalloc(92233720368547758) == NULL)
        cr_assert_eq(true, true);
    else
        cr_assert_eq(true, false);
}

Test(functions_limit, free_null_ptr)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mfree)(void *ptr) = dlsym(handle, "free");

    free(NULL);
}