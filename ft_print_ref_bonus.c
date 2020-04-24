#include "ft_printf_bonus.h"

static int  left_print(f_mod_struct *f_mod)
{
	int blank_width;
	int	prnt_cnt;

	blank_width = f_mod->width > f_mod->precision ? f_mod->width - f_mod->precision : 0;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(f_mod->precision, '0');
	prnt_cnt += ft_print_repeat(blank_width, ' ');	
	return (prnt_cnt);
}

static int  right_print(f_mod_struct *f_mod)
{
	int blank_width;
	int	fill_char;
	int	prnt_cnt;

	blank_width = f_mod->width > f_mod->precision ? f_mod->width - f_mod->precision : 0;
	fill_char = ' ';	
	if (f_mod->zero && !f_mod->dot)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	prnt_cnt += ft_print_repeat(f_mod->precision, '0');
	return (prnt_cnt);
}

int	ft_print_ref(va_list ap, f_mod_struct *f_mod, int print_counter)
{
	unsigned long	u;
	int				*i;
	long int		*li;
	int				prnt_cnt;

	u = va_arg(ap, unsigned long);
	li = f_mod->l ? (long int *)u : 0;
	i = !f_mod->l ? (int *)u : 0;
	if (f_mod->l)
		*li = print_counter;
	else
		*i = print_counter;
	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod);
	else
		prnt_cnt += right_print(f_mod);
	return (prnt_cnt);
}