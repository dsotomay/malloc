NAME = libft.a
HEADER = -c
FLAGS = -g -Wall -Wextra -Werror
CONFIG = gcc $(HEADER) $(FLAGS) $(SRC)
CONFIG2 = ar rc $(NAME) $(OBJ) $(PRINTF)
CONFIG3 = ranlib $(NAME)
PRINTF = ft_printf/*.o
SRC = ft_abs.c \
ft_arrlen.c \
ft_atoi.c \
ft_bzero.c \
ft_cmptill.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_itoa_base.c \
ft_lstadd.c \
ft_lstdel.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstmap.c \
ft_lstnew.c \
ft_memalloc.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memdel.c \
ft_memmove.c \
ft_memset.c \
ft_putchar.c \
ft_putchar_fd.c \
ft_putendl.c \
ft_putendl_fd.c \
ft_putnbr.c \
ft_putnbr_fd.c \
ft_putstr.c \
ft_putstr_fd.c \
ft_queue.c \
ft_realloc.c \
ft_strcat.c \
ft_strchr.c \
ft_strclr.c \
ft_strcmp.c \
ft_strcpy.c \
ft_strcspn.c \
ft_strdel.c \
ft_strdup.c \
ft_strequ.c \
ft_striter.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlen.c \
ft_strmap.c \
ft_strmapi.c \
ft_strncat.c \
ft_strncmp.c \
ft_strncpy.c \
ft_strnequ.c \
ft_strnew.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strsplit.c \
ft_strspn.c \
ft_strstr.c \
ft_strsub.c \
ft_strtok.c \
ft_strtrim.c \
ft_swap.c \
ft_swap_array.c \
ft_tolower.c \
ft_toupper.c \
ft_utoa_base.c \
ft_ws_to_strncpy.c \
ft_wstrlen.c \
get_next_line.c

OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(NAME) $(PRINTF)

$(PRINTF):
	make -C ft_printf/

$(NAME): $(SRC) $(PRINTF)
	$(CONFIG)
	$(CONFIG2)
	$(CONFIG3)

clean:
	/bin/rm -f $(OBJ)
	make clean -C ft_printf/

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C ft_printf/

re: fclean all
