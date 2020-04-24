#include "ft_printf_bonus.h"

static int	left_print(f_mod_struct *f_mod, char *str, int str_len)
{
	int		blank_width;
	char	fill_char;
	int		prnt_cnt;

	if (f_mod->precision && f_mod->precision < str_len)
		str_len = f_mod->precision;
	blank_width = f_mod->width > str_len ? f_mod->width - str_len : 0;
	fill_char = ' ';
	if (f_mod->zero)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += write(1, str, str_len);
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	return (prnt_cnt);
}

static int	right_print(f_mod_struct *f_mod, char *str, int str_len)
{
	int		blank_width;
	char	fill_char;
	int		prnt_cnt;

	if (f_mod->precision && f_mod->precision < str_len)
		str_len = f_mod->precision;
	blank_width = f_mod->width > str_len ? f_mod->width - str_len : 0;
	fill_char = ' ';
	if (f_mod->zero)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	prnt_cnt += write(1, str, str_len);
	return (prnt_cnt);
}

int			ft_print_str(va_list ap, f_mod_struct *f_mod)
{
	char	*str;
	wchar_t	*lstr;
	int		str_len;
	int		prnt_cnt;

	lstr = f_mod->l ? va_arg(ap, wchar_t *) : 0;
	str = !f_mod->l ? va_arg(ap, char *) : 0;
	if (!lstr && f_mod->l)
		lstr = (wchar_t *)"(null)";
	if (!str && !f_mod->l)
		str = "(null)";	
	str_len = 0;	
	str_len = ft_strlen(str);	
	if (f_mod->dot && !f_mod->precision)
		str_len = 0;
	prnt_cnt = 0;
	if (f_mod->minus && f_mod->l)
		prnt_cnt += left_print(f_mod, (char *)lstr, str_len);		
	else if (f_mod->minus)
		prnt_cnt += left_print(f_mod, str, str_len);
	else if (f_mod->l)
		prnt_cnt += right_print(f_mod, (char *)lstr, str_len);
	else
		prnt_cnt += right_print(f_mod, str, str_len);
	return (prnt_cnt);
}
