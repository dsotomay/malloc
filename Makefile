ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
NAMELN = libft_malloc.so
HEADER = -c
FLAGS = -g -Wall -Wextra -Werror
CONFIG = gcc $(HEADER) $(FLAGS) $(OBJ) -o $(NAME)
LIBFT = libft/libft.a
SRC = malloc.c realloc.c free.c
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft/

$(NAME): $(SRC) $(LIBFT)
	$(CONFIG)
	ln -s $(NAME) $(NAMELN)

$(TEST):
	gcc -g malloc.c sbrk.c test.c

clean:
	/bin/rm -f $(OBJ)
	make clean -C ft_printf/

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(NAMELN)
	make fclean -C libft/

re: fclean all
