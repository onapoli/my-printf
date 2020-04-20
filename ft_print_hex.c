#include "ft_printf.h"

static int  left_print(f_mod_struct *f_mod, char *num_char, int str_len)
{
	int	blank_precision;
	int	blank_width;
	int	prnt_cnt;

	blank_precision = f_mod->precision > str_len ? f_mod->precision - str_len : 0;
	blank_width = f_mod->width > (blank_precision + str_len) ? f_mod->width - blank_precision - str_len : 0;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int  right_print(f_mod_struct *f_mod, char *num_char, int str_len)
{
	int	blank_precision;
	int blank_width;
	int	fill_char;
	int	prnt_cnt;

	blank_precision = f_mod->precision > str_len ? f_mod->precision - str_len : 0;
	blank_width = f_mod->width > (blank_precision + str_len) ? f_mod->width - blank_precision - str_len : 0;
	fill_char = ' ';	
	if (f_mod->zero && !f_mod->dot)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	return (prnt_cnt);
}

int			ft_print_hex(va_list ap, f_mod_struct *f_mod, char hex_type)
{
    unsigned int    h;
    char            *num_char;
    int             str_len;
    int             prnt_cnt;

    h = va_arg(ap, unsigned int);
    num_char = ft_itox(h, hex_type);
    str_len = ft_strlen(num_char);
    if (f_mod->dot && !f_mod->precision && !h)
		str_len = 0;
    prnt_cnt = 0;
    if (f_mod->minus)
		prnt_cnt += left_print(f_mod, num_char, str_len);
	else
		prnt_cnt += right_print(f_mod, num_char, str_len);
	free(num_char);
    return (prnt_cnt);
}