/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <onapoli-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:58:31 by onapoli-          #+#    #+#             */
/*   Updated: 2020/05/29 15:58:33 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int  left_print(f_mod_struct *f_mod, char *num_char, int str_len, char hex_type)
{
	int		blank_precision;
	int		blank_width;
	int 	zero_x;
	char	*x_char;
	int		prnt_cnt;

	x_char = hex_type == 'x' ? "0x" : "0X";
	zero_x = f_mod->hash ? 2 : 0;
	blank_precision = f_mod->precision > str_len ? f_mod->precision - str_len : 0;
	blank_width = f_mod->width > (blank_precision + str_len +zero_x) ?
		f_mod->width - blank_precision - str_len - zero_x : 0;
	prnt_cnt = 0;
	prnt_cnt += write(1, x_char, zero_x);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int  right_print(f_mod_struct *f_mod, char *num_char, int str_len, char hex_type)
{
	int		blank_precision;
	int 	blank_width;
	int		fill_char;
	int 	zero_x;
	char	*x_char;
	int		prnt_cnt;

	x_char = hex_type == 'x' ? "0x" : "0X";
	zero_x = f_mod->hash ? 2 : 0;
	blank_precision = f_mod->precision > str_len ? f_mod->precision - str_len : 0;
	blank_width = f_mod->width > (blank_precision + str_len + zero_x) ?
		f_mod->width - blank_precision - str_len - zero_x : 0;
	fill_char = ' ';	
	if (f_mod->zero && !f_mod->dot)
		fill_char = '0';
	prnt_cnt = 0;
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	prnt_cnt += write(1, x_char, zero_x);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	return (prnt_cnt);
}

int			ft_print_hex(va_list ap, f_mod_struct *f_mod, char hex_type)
{
    unsigned int    	h;
	unsigned long int	lh;
    char            	*num_char;
    int             	str_len;
    int             	prnt_cnt;

	lh = f_mod->l ? va_arg(ap, unsigned long int) : 0;
	h = !f_mod->l ? va_arg(ap, unsigned int) : 0;
    num_char = f_mod->l ? ft_itox(lh, hex_type) : ft_itox(h, hex_type);
    str_len = ft_strlen(num_char);
    if (f_mod->dot && !f_mod->precision && (!h && !lh))
		str_len = 0;
    prnt_cnt = 0;
    if (f_mod->minus)
		prnt_cnt += left_print(f_mod, num_char, str_len, hex_type);
	else
		prnt_cnt += right_print(f_mod, num_char, str_len, hex_type);
	free(num_char);
    return (prnt_cnt);
}
