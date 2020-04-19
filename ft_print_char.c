#include "ft_printf.h"

int	ft_print_char(va_list ap, f_mod_struct *f_mod)
{
	int	c;
	int	before;
	int	after;
	int	prnt_cnt;

	c = va_arg(ap, int);
	if (!f_mod->width)
		f_mod->width = 1;
	if (f_mod->minus)
	{
		before = 0;
		after = f_mod->width - 1;
	}
	else
	{
		before = f_mod->width - 1;
		after = 0;
	}
	prnt_cnt = 0;
	while (before--)
		prnt_cnt += write(1, " ", 1);
	prnt_cnt += write(1, &c, 1);
	while (after--)
		prnt_cnt += write(1, " ", 1);
	return (prnt_cnt);
}