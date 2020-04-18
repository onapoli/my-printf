NAME = libftprintf.a

FT_PRINTF_SRC = ft_printf.c \
				ft_print_char.c \
				ft_print_str.c \
				ft_print_number.c \
				ft_print_unsigned.c \
				ft_printf_utils.c \
				ft_printf_utils_2.c \
				ft_printf_itoa.c

OBJ += $(FT_PRINTF_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all