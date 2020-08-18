/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:59:17 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/18 12:11:05 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	print_left(t_modifier *f_mod, char c)
{
	int blank_width;
	int	prnt_cnt;

	blank_width = f_mod->width - 1;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	prnt_cnt += write(1, &c, 1);
	return (prnt_cnt);
}

static int	print_right(t_modifier *f_mod, char c)
{
	int blank_width;
	int	prnt_cnt;

	blank_width = f_mod->width - 1;
	prnt_cnt = 0;
	prnt_cnt += write(1, &c, 1);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

int			ft_print_char(va_list ap, t_modifier *f_mod)
{
	int		c;
	wint_t	lc;
	int		prnt_cnt;

	lc = f_mod->l ? va_arg(ap, wint_t) : 0;
	c = !f_mod->l ? va_arg(ap, int) : 0;
	prnt_cnt = 0;
	if (f_mod->minus && f_mod->l)
		prnt_cnt += print_left(f_mod, (char)lc);
	else if (f_mod->minus)
		prnt_cnt += print_left(f_mod, c);
	else if (f_mod->l)
		prnt_cnt += print_right(f_mod, (char)lc);
	else
		prnt_cnt += print_right(f_mod, c);
	return (prnt_cnt);
}
