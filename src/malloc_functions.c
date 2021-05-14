/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** malloc_functions
*/

#include "libmalloc.h"

t_block *find_block(t_block **last, size_t size)
{
    t_block *b = (*last);
    t_block *best = NULL;

    while (b != NULL) {
        *last = b;
        if (b->free == 1 && size <= b->size) {
            if (best == NULL)
                best = b;
            if (best->size > size)
                best = b;
        }
        b = b->next;
    }
    if (best) {
        *last = best;
        return best;
    }
    return b;
}

void split_block(t_block **last, size_t size)
{
    t_block *newFree;
    size_t oldSize = (*last)->size;

    if ((*last)->size < size + BLOCK_SIZE &&
    (*last)->size >= size) {
        (*last)->free = 0;
        return;
    }
    (*last)->size = size;
    newFree = (void *)(*last)->data + (*last)->size;
    newFree->data = (void *)newFree + BLOCK_SIZE;
    newFree->free = 1;
    newFree->next = (*last)->next;
    newFree->prev = (*last);
    newFree->size = oldSize - (*last)->size - BLOCK_SIZE;
    (*last)->next = newFree;
    (*last)->free = 0;
}

size_t align_power_two(size_t size)
{
    size_t power;

    for (power = 1; power <= size; power *= 2)
        if (power * 2 > 92233720368547758)
            return 92233720368547758;
    return power;
}
