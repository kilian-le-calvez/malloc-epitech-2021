##
## EPITECH PROJECT, 2021
## B-PSU-400-PAR-4-1-malloc-kilian.le-calvez
## File description:
## Makefile
##

NAME		=		libmy_malloc.so

CC			=		gcc

CPPFLAGS	=		-I ./include

CFLAGS		=		-Wall -Wextra -fpic -ggdb -Werror

SRC			=		src/main_functions.c			\
					src/malloc_functions.c			\
					src/free_functions.c			\
					src/building.c

OBJ			=		$(SRC:.c=.o)

TSRC		=		tests/test_malloc.c					\
					tests/test_free.c					\
					tests/test_calloc_reallocarray.c	\
					tests/test_random.c					\
					tests/test_realloc.c				\
					tests/test_functions.c				\
					tests/test_building.c

TNAME		=		unit-tests

all: $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(LDLIBS)

compil_tests:
	$(CC) -o $(TNAME) $(TSRC) -lcriterion -ldl

tests_run: LDLIBS += -lgcov
tests_run: CFLAGS += -ggdb --coverage
tests_run: re compil_tests
	./$(TNAME)

clean:
	rm -f $(OBJ)
	rm -f $(wildcard */*.gcda)
	rm -f $(wildcard */*.gcno)
	rm -f tests/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(TNAME)

re: fclean all

.PHONY: all clean fclean re
