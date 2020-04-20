#include "ft_printf.h"

int     ft_add_number(int number, char addition)
{
	return ((number * 10) + (addition - '0'));
}

int     ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void    ft_init_structure(f_mod_struct *f_mod)
{
	f_mod->minus = 0;
	f_mod->width = 0;
	f_mod->zero = 0;
	f_mod->dot = 0;
	f_mod->precision = 0;
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*int		ft_check_type(char c)
{
	char	*types;

	types = "csdiuXxp";
	while (*types)
	{
		if (*types == c)
			return (1);
		types++;
	}
	return (0);
}*/
