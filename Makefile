# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/19 23:40:03 by dysotoma          #+#    #+#              #
#    Updated: 2019/10/05 16:42:39 by dysotoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ifeq ($(HOSTTYPE),)
# 	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
# endif

# NAME = libft_malloc_$(HOSTTYPE).so
# NAMELN = libft_malloc.so
# HEADER = -c
# FLAGS = -g -Wall -Wextra -Werror
# CONFIG = gcc $(FLAGS) $(HEADER) $(SRC)
# CONFIG2 = gcc -g -fPIC -shared -o $(NAME) $(OBJ) $(LIBFT)
# LIBFT = libft/libft.a
# SRC = malloc.c init.c block.c print_mem.c
# OBJ = $(patsubst %.c, %.o, $(SRC))

# all: $(NAME) $(LIBFT)
# :
# $(LIBFT):
# 	make -C libft/

# $(NAME): $(OBJ) $(LIBFT)
# 	$(CONFIG)
# 	$(CONFIG2)
# 	ln -s $(NAME) $(NAMELN)

# test:
# 	make -C libft/
# 	gcc -g -Wall -Wextra -Werror malloc.c init.c block.c print_mem.c \
# 	libft/libft.a test.c -fPIC

# clean:
# 	/bin/rm -f $(OBJ)
# 	make clean -C libft/

# fclean: clean
# 	/bin/rm -f $(NAME)
# 	/bin/rm -f $(NAMELN)
# 	make fclean -C libft/

# re: fclean all 

# .PHONY: setenv unsetenv test all clean fclean

# setenv:
# 	@echo "export DYLD_FORCE_FLAT_NAMESPACE=1"
# 	@echo "export DYLD_LIBRARY_PATH=."
# 	@echo "export DYLD_INSERT_LIBRARIES=$(NAME)"
# 	@echo "# Run eval \$$(make setenv)"

# unsetenv:
# 	@echo "unset DYLD_LIBRARY_PATH"
# 	@echo "unset DYLD_INSERT_LIBRARIES"
# 	@echo "unset DYLD_FORCE_FLAT_NAMESPACE"
# 	@echo "# Run eval \$$(make unsetenv)"
#-Wl,-exported_symbol,_malloc -Wl,-exported_symbol,_free -Wl,-exported_symbol,_realloc -Wl,-exported_symbol,_show_alloc_mem -Wl,-exported_symbol,_calloc
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
NAMELN = libft_malloc.so
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
LIBFT = libft/libft.a
SRC = block.c init.c malloc.c print_mem.c find_free.c
OBJ	= $(SRC:%.c=%.o)

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	gcc -g -fPIC -shared -o $(NAME) $(CFLAGS) $(OBJ) $(LIBFT) 
	ln -sf $(NAME) $(NAMELN)

$(LIBFT):
	make -C libft/

test:
	make -C libft/
	gcc -g -Wall -Wextra -Werror malloc.c init.c block.c print_mem.c \
	libft/libft.a test.c -fPIC

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(NAMELN)
	make fclean -C libft/

re: fclean all 

.PHONY: setenv unsetenv test all clean fclean

setenv:
	@echo "export DYLD_FORCE_FLAT_NAMESPACE=1"
	@echo "export DYLD_LIBRARY_PATH=."
	@echo "export DYLD_INSERT_LIBRARIES=$(NAME)"
	@echo "# Run eval \$$(make setenv)"

unsetenv:
	@echo "unset DYLD_LIBRARY_PATH"
	@echo "unset DYLD_INSERT_LIBRARIES"
	@echo "unset DYLD_FORCE_FLAT_NAMESPACE"
	@echo "# Run eval \$$(make unsetenv)"


# #_____________CONFIG____________#

# ifeq ($(HOSTTYPE),)
# 	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
# endif

# LIBFT = libft/libft.a
# NAME = libft_malloc_$(HOSTTYPE).so
# NAME_LINK = libft_malloc.so

# PATH_SRC = ./src/

# PATH_INC = ./inc

# # PATH_INC_LIBFT = ./libft/includes/

# # INCLUDES = -I $(PATH_INC) -I $(PATH_INC_LIBFT)
# INCLUDES = -I $(PATH_INC)

# CC = cc

# ifeq ($(DEBUG),yes)
# 	CFLAGS = -g -fPIC
# 	LDFLAGS = -shared
# else
# 	CFLAGS = -Wall -Wextra -Werror -fPIC
# 	LDFLAGS = -shared
# endif

# # LIBS = -L libft/ -lft

# #_____________FILES____________#

# SRC = block.c init.c malloc.c print_mem.c find_free.c


# OBJ	= $(SRC:%.c=%.o)

# #____________RULES_____________#

# .PHONY: clean fclean re test

# all: $(NAME)

# $(NAME): $(OBJ) $(LIBFT)
# 	# make -C libft/
# 	# $(CC) $(OBJ) -o $(NAME) $(LIBS) $(LDFLAGS)
# 	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LIBFT)
# 	ln -s $(NAME) $(NAME_LINK)

# $(LIBFT):
# 	make -C libft/
	
# #____CLEAN____#

# clean:
# 	rm -f $(OBJ)

# #___FCLEAN___#

# fclean: clean
# 	rm -f $(NAME)
# 	rm -f $(NAME_LINK)

# #____RE____#

# re: fclean all
