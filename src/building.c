/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** malloc
*/

#include <string.h>
#include "libmalloc.h"

void *calloc(size_t nmemb, size_t size)
{
    return malloc(nmemb * size);
}

void fusion_next_block(t_block **b, size_t size)
{
    (*b)->size += (*b)->next->size + BLOCK_SIZE;
    if ((*b)->next->next == NULL) {
        (*b)->next = NULL;
    } else {
        (*b)->next = (*b)->next->next;
        (*b)->next->prev = (*b);
    }
    split_block(b, size);
}

void *realloc_error(void *ptr, size_t *s, size_t size, t_block **b)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    *s = align_power_two(align4(size));
    *b = ptr - BLOCK_SIZE;
    return "STATUS:OK";
}

void *realloc(void *ptr, size_t size)
{
    t_block *b;
    void *newPtr;
    size_t s;

    if (ptr == NULL)
        return malloc(size);
    if (realloc_error(ptr, &s, size, &b) == NULL)
        return NULL;
    if (b->next && b->next->free == 1 &&
    b->next->size + b->size + BLOCK_SIZE >= s) {
        fusion_next_block(&b, s);
        return b->data;
    } else {
        newPtr = malloc(size);
        memcpy(newPtr, b->data, b->size);
        free(ptr);
        return newPtr;
    }
    return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);
}