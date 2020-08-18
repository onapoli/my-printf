/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:54:06 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/18 12:12:59 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	left_print(t_modifier *f_mod, char *p_char, int str_len)
{
	int	blank_precision;
	int	blank_width;
	int	prnt_cnt;

	blank_precision =
	f_mod->precision > str_len ? f_mod->precision - str_len : 0;
	blank_width =
	f_mod->width > (blank_precision + (str_len + 2)) ? f_mod->width -
	blank_precision - (str_len + 2) : 0;
	prnt_cnt = 0;
	prnt_cnt += write(1, "0x", 2);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, p_char, str_len);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int	right_print(t_modifier *f_mod, char *p_char, int str_len)
{
	int	blank_precision;
	int blank_width;
	int	fill_char;
	int	prnt_cnt;

	blank_precision =
	f_mod->precision > str_len ? f_mod->precision - str_len : 0;
	blank_width =
	f_mod->width > (blank_precision + (str_len + 2)) ? f_mod->width -
	blank_precision - (str_len + 2) : 0;
	fill_char = ' ';
	if (f_mod->zero && !f_mod->dot)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	prnt_cnt += write(1, "0x", 2);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, p_char, str_len);
	return (prnt_cnt);
}

int			ft_print_pointer(va_list ap, t_modifier *f_mod)
{
	unsigned long	p;
	char			*p_char;
	int				str_len;
	int				prnt_cnt;

	p = va_arg(ap, unsigned long);
	p_char = ft_itox(p, 'x');
	str_len = ft_strlen(p_char);
	if (f_mod->dot && !f_mod->precision && !p)
		str_len = 0;
	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod, p_char, str_len);
	else
		prnt_cnt += right_print(f_mod, p_char, str_len);
	free(p_char);
	return (prnt_cnt);
}
