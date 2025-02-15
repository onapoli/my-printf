/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:51:28 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/18 12:06:25 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	left_print(t_modifier *f_mod, char *str, int str_len)
{
	int		blank_width;
	int		prnt_cnt;

	if (f_mod->precision && f_mod->precision < str_len)
		str_len = f_mod->precision;
	blank_width = f_mod->width > str_len ? f_mod->width - str_len : 0;
	prnt_cnt = 0;
	prnt_cnt += write(1, str, str_len);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int	right_print(t_modifier *f_mod, char *str, int str_len)
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

int			ft_print_str(va_list ap, t_modifier *f_mod)
{
	char	*str;
	int		str_len;
	int		prnt_cnt;

	str = va_arg(ap, char *);
	str_len = 0;
	if (!str)
		str = "(null)";
	str_len = ft_strlen(str);
	if (f_mod->dot && !f_mod->precision)
		str_len = 0;
	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod, str, str_len);
	else
		prnt_cnt += right_print(f_mod, str, str_len);
	return (prnt_cnt);
}
