/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** main_functions
*/

#include "libmalloc.h"

static t_block *head = NULL;

void *extend_mem(t_block **last, size_t size)
{
    int nb_pages = (size - 1 + BLOCK_SIZE) / PAGE_SIZE + 1;
    t_block *freeBlock;

    freeBlock = sbrk(0);
    if (sbrk((nb_pages * PAGE_SIZE) * 2) == (void *) - 1)
        return NULL;
    freeBlock->data = (void *)(freeBlock) + BLOCK_SIZE;
    freeBlock->free = 1;
    freeBlock->next = NULL;
    freeBlock->prev = (*last);
    freeBlock->size = (nb_pages * PAGE_SIZE) * 2 - BLOCK_SIZE;
    if (head == NULL) {
        head = freeBlock;
        (*last) = head;
    } else {
        (*last)->next = freeBlock;
        (*last) = (*last)->next;
    }
    fusion_back(last);
    return "STATUS:OK";
}

void *malloc(size_t size)
{
    t_block *b;
    t_block *last = head;
    size_t s = align_power_two(align4(size));

    b = find_block(&last, s);
    if (b == NULL)
        if (extend_mem(&last, s) == NULL)
            return NULL;
    split_block(&last, s);
    return last->data;
}

void fusion_and_free(t_block **b)
{
    fusion_back(b);
    fusion_forward(b);
    if ((*b)->next == NULL && (*b)->prev == NULL) {
        brk(head);
        head = NULL;
    } else if ((*b)->next == NULL) {
        (*b)->prev->next = NULL;
        brk((*b));
    }
}

void free(void *ptr)
{
    t_block *b;

    if (ptr != NULL) {
        b = ptr - BLOCK_SIZE;
        if (b && b->free == 0) {
            b->free = 1;
            fusion_and_free(&b);
        }
    }
}