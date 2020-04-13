#include "ft_printf.h"

int	ft_print_str(va_list ap, f_mod_struct *f_mod)
{
	char	*str;
	int		str_len;
	int		before;
	int		after;
	int		prnt_cnt;

	str = va_arg(ap, char *);	
	str_len = ft_strlen(str);	
	if (f_mod->minus)
	{
		before = 0;
		after = f_mod->width - str_len > 0 ? f_mod->width - str_len : 0;
	}
	else
	{
		before = f_mod->width - str_len > 0 ? f_mod->width - str_len : 0;
		after = 0;
	}
	prnt_cnt = 0;
	while (before--)
		prnt_cnt += write(1, " ", 1);
	prnt_cnt += write(1, str, str_len);
	while (after--)
		prnt_cnt += write(1, " ", 1);
	return (prnt_cnt);
}
