/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 13:02:35 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/24 18:03:18 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_print_no_flags_no_mods(char fmt_char, int *print_counter)
{
	if (fmt_char == '%')
		return ;
	write(1, &(fmt_char), 1);
	*print_counter += 1;
}

static void	last_case(char fmt_char, t_modifier *f_mod)
{
	if (!f_mod->asterisk)
		f_mod->precision = ft_add_number(f_mod->precision, fmt_char);
	else
	{
		f_mod->precision = ft_add_number(0, fmt_char);
		f_mod->asterisk = 0;
	}
}

void		process_flag_digit_or_asterisk(char fmt_char, t_modifier *f_mod,
va_list ap)
{
	if (fmt_char == '0' && !f_mod->zero && !f_mod->width && !f_mod->dot)
		f_mod->zero = 1;
	else if (!f_mod->dot && fmt_char == '*')
	{
		f_mod->width = va_arg(ap, int);
		f_mod->asterisk = 1;
	}
	else if (!f_mod->dot)
	{
		if (!f_mod->asterisk)
			f_mod->width = ft_add_number(f_mod->width, fmt_char);
		else
		{
			f_mod->width = ft_add_number(0, fmt_char);
			f_mod->asterisk = 0;
		}
	}
	else if (fmt_char == '*')
	{
		f_mod->precision = va_arg(ap, int);
		f_mod->asterisk = 1;
	}
	else
		last_case(fmt_char, f_mod);
}
