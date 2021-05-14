/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** free_functions
*/

#include "libmalloc.h"

void fusion_forward(t_block **b)
{
    while ((*b)->next != NULL && (*b)->next->free == 1) {
        (*b)->size += (*b)->next->size + BLOCK_SIZE;
        if ((*b)->next->next == NULL) {
            (*b)->next = NULL;
        } else {
            (*b)->next = (*b)->next->next;
            (*b)->next->prev = (*b);
        }
    }
}

void fusion_back(t_block **b)
{
    while ((*b)->prev != NULL && (*b)->prev->free == 1) {
        (*b) = (*b)->prev;
        fusion_forward(b);
    }
}