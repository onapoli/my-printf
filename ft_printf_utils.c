/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:44:02 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/18 12:09:14 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_add_number(int number, char addition)
{
	return ((number * 10) + (addition - '0'));
}

int		ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_init_structure(t_modifier *f_mod)
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

int		ft_print_repeat(int i, char c)
{
	int prnt_cnt;

	prnt_cnt = 0;
	while (i--)
		prnt_cnt += write(1, &c, 1);
	return (prnt_cnt);
}
