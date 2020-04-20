#include "ft_printf.h"

int			ft_print_repeat(int i, char c)
{
    int prnt_cnt;

    prnt_cnt = 0;
    while (i--)
		prnt_cnt += write(1, &c, 1);
    return (prnt_cnt);
}

/*int			ft_check_flag(char c)
{
	char	*flags;

	flags = "-.*0123456789";
	while (*flags)
	{
		if (*flags == c)
			return (1);
		flags++;
	}
	return (0);
}*/
