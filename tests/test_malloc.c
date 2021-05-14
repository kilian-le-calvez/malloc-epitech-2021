/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** test_malloc
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include "../include/libmalloc.h"

void fill_str(char c, int size, char **str);

Test(malloc_basics, simple_malloc)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    int len = 5;
    char *str = mmalloc(100);
    int i;

    for (i = 0; i < len; i++)
        str[i] = '0';
    str[i] = '\0';
    cr_assert_str_eq(str, "00000");
}

Test(malloc_basics, five_mallocs_little_size)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    char *str = mmalloc(100);
    fill_str('A', 5, &str);
    cr_assert_str_eq(str, "AAAAA");

    str = mmalloc(100);
    fill_str('B', 5, &str);
    cr_assert_str_eq(str, "BBBBB");

    str = mmalloc(100);
    fill_str('C', 5, &str);
    cr_assert_str_eq(str, "CCCCC");

    str = mmalloc(100);
    fill_str('D', 5, &str);
    cr_assert_str_eq(str, "DDDDD");
}

Test(malloc_basics, five_mallocs_extend_heap)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void (*dump)() = dlsym(handle, "dump");
    char *str = mmalloc(100);
    fill_str('A', 5, &str);
    cr_assert_str_eq(str, "AAAAA");

    str = mmalloc(8000);
    fill_str('B', 5, &str);
    cr_assert_str_eq(str, "BBBBB");

    str = mmalloc(8000);
    fill_str('C', 5, &str);
    cr_assert_str_eq(str, "CCCCC");

    str = mmalloc(8000);
    fill_str('D', 5, &str);
    cr_assert_str_eq(str, "DDDDD");
}

Test(malloc_basics, perfect_use_free_block_size)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*mmalloc)(size_t size) = dlsym(handle, "malloc");
    void (*mfree)(void *ptr) = dlsym(handle, "free");
    char *str = mmalloc(100);
    str = mmalloc(100);
    str = mmalloc(100);
    mfree(str);
    str = mmalloc(100);
    str = mmalloc(100);
    fill_str('A', 5, &str);
    cr_assert_str_eq(str, "AAAAA");

}

Test(malloc_error, TOO_big_extendmem)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*extend_mem)(t_block **b, size_t size) =
    dlsym(handle, "extend_mem");
    void *ptr;

    ptr = extend_mem(NULL, 92233720368547758);
    cr_assert_eq(NULL, ptr);
}