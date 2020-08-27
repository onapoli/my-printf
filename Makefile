NAME = libftprintf.a

FT_PRINTF_SRC = ft_printf.c \
				ft_print_char.c \
				ft_print_str.c \
				ft_print_number.c \
				ft_print_unsigned.c \
				ft_print_hex.c \
				ft_print_pointer.c \
				ft_print_empty.c \
				ft_print_percent.c \
				ft_printf_utils.c \
				ft_printf_utils_2.c \
				ft_printf_itoa.c \
				ft_printf_itox.c

OBJ = $(FT_PRINTF_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
