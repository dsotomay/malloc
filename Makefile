# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/19 23:40:03 by dysotoma          #+#    #+#              #
#    Updated: 2019/09/19 23:40:04 by dysotoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

test:
	make -C libft/
	gcc -g -Wall -Wextra -Werror malloc.c init.c block.c libft/libft.a

clean:
	/bin/rm -f $(OBJ)
	make clean -C ft_printf/

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(NAMELN)
	make fclean -C libft/

re: fclean all
