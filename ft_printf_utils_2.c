#include "ft_printf.h"

int ft_print_repeat(int i, char c)
{
    int prnt_cnt;

    prnt_cnt = 0;
    while (i--)
		prnt_cnt += write(1, &c, 1);
    return (prnt_cnt);
}