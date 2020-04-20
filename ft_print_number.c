#include "ft_printf.h"

static int	print_n_count_sign(char **num_char, int *str_len, int sign)
{
	if (!sign)
		return (0);
	*num_char += 1;
	*str_len -= 1;
	return (write(1, "-", 1));
}

static int	left_print(f_mod_struct *f_mod, char *num_char, int str_len, int sign)
{
	int	blank_precision;
	int blank_width;
	int	prnt_cnt;

	blank_precision = f_mod->precision > (str_len - sign) ? f_mod->precision - str_len + sign : 0;
	blank_width = f_mod->width > (blank_precision + str_len) ? f_mod->width - blank_precision - str_len : 0;
	prnt_cnt = 0;
	if (*num_char == '-')
		prnt_cnt += print_n_count_sign(&num_char, &str_len, sign);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int	right_print(f_mod_struct *f_mod, char *num_char, int str_len, int sign)
{
	int	blank_precision;
	int blank_width;
	int	fill_char;
	int	prnt_cnt;

	blank_precision = f_mod->precision > (str_len - sign) ? f_mod->precision - str_len + sign : 0;
	blank_width = f_mod->width > (blank_precision + str_len) ? f_mod->width - blank_precision - str_len : 0;
	fill_char = ' ';
	prnt_cnt = 0;
	if (f_mod->zero && !f_mod->dot)
	{
		fill_char = '0';
		prnt_cnt += print_n_count_sign(&num_char, &str_len, sign);
	}
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	if (*num_char == '-')
		prnt_cnt += print_n_count_sign(&num_char, &str_len, sign);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	return (prnt_cnt);
}

int			ft_print_number(va_list ap, f_mod_struct *f_mod)
{
	int		num;
	char	*num_char;
	int		str_len;
	int		sign;
	int		prnt_cnt;

	num = va_arg(ap, int);
	num_char = ft_itoa(num);
	str_len = ft_strlen(num_char);
	if (f_mod->dot && !f_mod->precision && !num)
		str_len = 0;
	sign = *num_char == '-' ? 1 : 0;
	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod, num_char, str_len, sign);
	else
		prnt_cnt += right_print(f_mod, num_char, str_len, sign);
	free(num_char);	
	return (prnt_cnt);
}