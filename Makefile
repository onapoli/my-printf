NAME = libftprintf.a

FT_PRINTF_SRC = 		ft_printf.c \
						ft_print_char.c \
						ft_print_str.c \
						ft_print_number.c \
						ft_print_unsigned.c \
						ft_print_hex.c \
						ft_print_pointer.c \
						ft_print_empty.c \
						ft_print_percent.c \
						ft_printf_utils.c \
						ft_printf_itoa.c \
						ft_printf_itox.c

FT_PRINTF_SRC_BONUS = 	ft_printf_bonus.c \
						ft_print_char_bonus.c \
						ft_print_str_bonus.c \
						ft_print_number_bonus.c \
						ft_print_unsigned_bonus.c \
						ft_print_hex_bonus.c \
						ft_print_pointer_bonus.c \
						ft_print_ref_bonus.c \
						ft_print_empty_bonus.c \
						ft_print_percent_bonus.c \
						ft_printf_utils_bonus.c \
						ft_printf_itoa_bonus.c \
						ft_printf_itox_bonus.c

OBJ += $(FT_PRINTF_SRC:.c=.o)
OBJ_BONUS += $(FT_PRINTF_SRC_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(OBJ_BONUS)
	@ar rc $(NAME) $(OBJ) $(OBJ_BONUS)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean bonus

.PHONY: all bonus clean fclean re
