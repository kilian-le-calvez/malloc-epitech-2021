/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
** File description:
** libmalloc
*/

#ifndef LIBMALLOC_H_
#define LIBMALLOC_H_

#include <unistd.h>
#include <sys/types.h>

typedef struct s_block t_block;

struct s_block {
    size_t size;
    t_block *prev;
    t_block *next;
    int free;
    void *data;
};

#define align4(x) (((((x)-1) >> 2) << 2)+4)
#define BLOCK_SIZE align4(sizeof(t_block))
#define PAGE_SIZE getpagesize()

//minilib
int my_strlen(char *str);
char *my_strcpy(char *str);
void my_putnbr(size_t nb);
void my_putstr(char *str);

//main functions
void dump();
void *extend_mem(t_block **last, size_t size);
void *malloc(size_t size);
void fusion_and_free(t_block **b);
void free(void *ptr);

//malloc functions
t_block *find_block(t_block **last, size_t size);
void split_block(t_block **last, size_t size);
size_t align_power_two(size_t size);

//free functions
void fusion_forward(t_block **b);
void fusion_back(t_block **b);

//building
void *calloc(size_t  nmemb, size_t  size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif /* !LIBMALLOC_H_ */