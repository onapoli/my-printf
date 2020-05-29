/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <onapoli-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:58:41 by onapoli-          #+#    #+#             */
/*   Updated: 2020/05/29 15:58:43 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	left_print(f_mod_struct *f_mod)
{
	int	blank_precision;
	int blank_width;
	int	prnt_cnt;

	blank_precision = f_mod->precision;
	blank_width = f_mod->width > blank_precision ? f_mod->width - blank_precision : 0;
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += ft_print_repeat(blank_width, ' ');		
	return (prnt_cnt);
}

static int	right_print(f_mod_struct *f_mod)
{
	int		blank_precision;
	int		blank_width;
	char	fill_char;
	int	prnt_cnt;

	blank_precision = f_mod->precision;
	blank_width = f_mod->width > blank_precision ? f_mod->width - blank_precision : 0;
	fill_char = ' ';
	if (f_mod->zero && !f_mod->dot)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	prnt_cnt += ft_print_repeat(blank_precision, '0');	
	return (prnt_cnt);
}

int			ft_print_empty(f_mod_struct *f_mod)
{
	int	prnt_cnt;

	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod);
	else
		prnt_cnt += right_print(f_mod);
	return (prnt_cnt);
}
