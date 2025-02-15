/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:43:26 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/24 18:02:33 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_process_flag(const char *fmt, va_list ap, t_modifier *f_mod)
{
	if (*fmt == '-')
		f_mod->minus = 1;
	if (*fmt == '.')
	{
		f_mod->dot = 1;
		f_mod->asterisk = 0;
	}
	if (ft_is_digit(*fmt) || *fmt == '*')
	{
		process_flag_digit_or_asterisk(*fmt, f_mod, ap);
		if (*fmt == '*' && (f_mod->width < 0 || f_mod->precision < 0))
			f_mod->minus = 1;
		f_mod->dot = f_mod->precision < 0 ? 0 : f_mod->dot;
		f_mod->width = f_mod->width < 0 ? f_mod->width * -1 : f_mod->width;
		f_mod->precision = f_mod->precision < 0 ? 0 : f_mod->precision;
	}
	return (0);
}

static int	ft_process_type(const char *fmt, va_list ap, t_modifier *f_mod,
int *print_counter)
{
	if (*fmt == 'c')
		*print_counter += ft_print_char(ap, f_mod);
	else if (*fmt == 's')
		*print_counter += ft_print_str(ap, f_mod);
	else if (*fmt == 'd' || *fmt == 'i')
		*print_counter += ft_print_number(ap, f_mod);
	else if (*fmt == 'u')
		*print_counter += ft_print_unsigned(ap, f_mod);
	else if (*fmt == 'X')
		*print_counter += ft_print_hex(ap, f_mod, 'X');
	else if (*fmt == 'x')
		*print_counter += ft_print_hex(ap, f_mod, 'x');
	else if (*fmt == 'p')
		*print_counter += ft_print_pointer(ap, f_mod);
	else if (*fmt == '%')
		*print_counter += ft_print_percent(f_mod);
	else if (*fmt)
		*print_counter += ft_print_empty(f_mod, 1);
	else
		*print_counter += ft_print_empty(f_mod, 0);
	return (0);
}

static int	ft_check_char_in_str(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static int	ft_format(const char *fmt, va_list ap, int *print_counter)
{
	int				fmt_pos;
	t_modifier		*f_mod;

	fmt_pos = 1;
	fmt++;
	if (!(f_mod = malloc(sizeof(t_modifier))))
		return (-1);
	ft_init_structure(f_mod);
	while (ft_check_char_in_str(*fmt, "-.*0123456789"))
	{
		ft_process_flag(fmt, ap, f_mod);
		fmt++;
		fmt_pos++;
	}
	ft_process_type(fmt, ap, f_mod, print_counter);
	if (ft_check_char_in_str(*fmt, "csdiuXxp%"))
		fmt_pos++;
	free(f_mod);
	return (fmt_pos);
}

int			ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		print_counter;

	va_start(ap, fmt);
	print_counter = 0;
	while (*fmt)
	{
		if (*fmt == '%' && fmt[1] == '%')
		{
			write(1, "%", 1);
			print_counter++;
			fmt += 2;
		}
		else if (*fmt == '%' &&
		ft_check_char_in_str(fmt[1], "-.*0123456789csdiuXxp"))
			fmt += ft_format(&(*fmt), ap, &print_counter);
		else
		{
			handle_print_no_flags_no_mods(*fmt, &print_counter);
			fmt++;
		}
	}
	va_end(ap);
	return (print_counter);
}
