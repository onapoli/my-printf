/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <onapoli-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:48:52 by onapoli-          #+#    #+#             */
/*   Updated: 2020/05/29 15:48:54 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_process_flag(const char *fmt, va_list ap, f_mod_struct *f_mod)
{
	f_mod->minus = *fmt == '-' ? 1 : f_mod->minus;
	f_mod->dot = *fmt == '.' ? 1 : f_mod->dot;
	f_mod->hash = *fmt == '#' ? 1 : f_mod->hash;
	f_mod->plus = *fmt == '+' ? 1 : f_mod->plus;
	f_mod->l = *fmt == 'l' ? 1 : f_mod->l;
	f_mod->space = *fmt == ' ' ? 1 : f_mod->space;
	if (ft_is_digit(*fmt) || *fmt == '*')
	{
		if (*fmt == '0' && !f_mod->zero && !f_mod->width && !f_mod->dot)
			f_mod->zero = 1;
		else if (!f_mod->dot && *fmt == '*')
			f_mod->width = va_arg(ap, int);
		else if (!f_mod->dot)
			f_mod->width = ft_add_number(f_mod->width, *fmt);
		else if (*fmt == '*')
			f_mod->precision = va_arg(ap, int);
		else
			f_mod->precision = ft_add_number(f_mod->precision, *fmt);
		if (*fmt == '*' && (f_mod->width < 0 || f_mod->precision < 0))
			f_mod->minus = 1;		
		f_mod->dot = f_mod->precision < 0 ? 0 : f_mod->dot;
		f_mod->width = f_mod->width < 0 ? f_mod->width * -1 : f_mod->width;
		f_mod->precision = f_mod->precision < 0 ? 0 : f_mod->precision;
	}
	return (0); 
}

static int	ft_process_type(const char *fmt, va_list ap, f_mod_struct *f_mod, int *print_counter)
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
	else if (*fmt == 'n')
		*print_counter += ft_print_ref(ap, f_mod, *print_counter);
	else if (*fmt == 'p')
		*print_counter += ft_print_pointer(ap, f_mod);
	else if (*fmt == '%')
		*print_counter += ft_print_percent(f_mod);
	else
		*print_counter += ft_print_empty(f_mod);	
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
	f_mod_struct	*f_mod;

	fmt_pos = 1; //PARA INCLUIR LA POSICIÓN DEL %
	fmt++; //PARA AVANZAR AL CARACTER QUE ESTÁ DESPUÉS DEL %
	if (!(f_mod = malloc(sizeof(f_mod_struct))))
		return (-1);
	ft_init_structure(f_mod);
	while (ft_check_char_in_str( *fmt, "-.*+l #0123456789"))
	{		
		ft_process_flag(fmt, ap, f_mod);						
		fmt++;
		fmt_pos++;
	}
	ft_process_type(fmt, ap, f_mod, print_counter);
	if (ft_check_char_in_str(*fmt, "csdiuXxpn%"))
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
		else if (*fmt == '%' && ft_check_char_in_str(fmt[1], "-.*#+l 0123456789csdiuXxpn"))
			fmt += ft_format(&*fmt, ap, &print_counter);
		else
		{
			write(1, &*fmt, 1);
			print_counter++;
			fmt++;
		}						
	}
    va_end(ap);	
	return (print_counter);
}
