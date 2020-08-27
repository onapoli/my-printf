/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:58:41 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/24 12:55:30 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	left_print(t_modifier *f_mod, int str_len)
{
	int blank_width;
	int	prnt_cnt;

	blank_width =
	f_mod->width > str_len ? f_mod->width - str_len : 0;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int	right_print(t_modifier *f_mod, int str_len)
{
	int		blank_width;
	char	fill_char;
	int		prnt_cnt;

	blank_width =
	f_mod->width > str_len ? f_mod->width - str_len : 0;
	fill_char = ' ';
	if (f_mod->zero)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	return (prnt_cnt);
}

int			ft_print_empty(t_modifier *f_mod, int next_char)
{
	int	str_len;
	int	prnt_cnt;

	str_len = 0;
	if (next_char)
		str_len = 1;
	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod, str_len);
	else
		prnt_cnt += right_print(f_mod, str_len);
	return (prnt_cnt);
}
