#include "ft_printf.h"

static int	left_print(f_mod_struct *f_mod)
{
	int	blank_precision;
	int blank_width;
	int	prnt_cnt;

	blank_precision = f_mod->precision;
	blank_width = f_mod->width > blank_precision ? f_mod->width - blank_precision : 0;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	prnt_cnt += ft_print_repeat(blank_precision, '0');	
	return (prnt_cnt);
}

static int	right_print(f_mod_struct *f_mod)
{
	int	blank_precision;
	int blank_width;
	int	prnt_cnt;

	blank_precision = f_mod->precision;
	blank_width = f_mod->width > blank_precision ? f_mod->width - blank_precision : 0;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

int			ft_print_empty(f_mod_struct *f_mod)
{
	int	prnt_cnt;

	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod);
	else
		prnt_cnt += right_print(f_mod);
	return (prnt_cnt);
}