/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:57:14 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/18 13:12:53 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	print_plus_or_space(t_modifier *f_mod, int sign)
{
	if (sign)
		return (0);
	if (f_mod->plus)
		return (write(1, "+", 1));
	if (f_mod->space)
		return (write(1, " ", 1));
	return (0);
}

static int	print_n_count_sign(char **num_char, int *str_len, int sign)
{
	if (!sign)
		return (0);
	*num_char += 1;
	*str_len -= 1;
	return (write(1, "-", 1));
}

static int	left_print(t_modifier *f_mod, char *num_char, int str_len,
int sign)
{
	int	blank_precision;
	int blank_width;
	int	plus_or_space;
	int	prnt_cnt;

	plus_or_space = !sign ? 1 : 0;
	blank_precision =
	f_mod->precision > (str_len - sign) ? f_mod->precision - str_len + sign : 0;
	blank_width = f_mod->width > (blank_precision + str_len + plus_or_space) ?
		f_mod->width - blank_precision - str_len - plus_or_space : 0;
	prnt_cnt = 0;
	if (*num_char == '-')
		prnt_cnt += print_n_count_sign(&num_char, &str_len, sign);
	prnt_cnt += print_plus_or_space(f_mod, sign);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	prnt_cnt += ft_print_repeat(blank_width, ' ');
	return (prnt_cnt);
}

static int	right_print(t_modifier *f_mod, char *num_char, int str_len,
int sign)
{
	int	blank_precision;
	int blank_width;
	int	fill_char;
	int	plus_or_space;
	int	prnt_cnt;

	plus_or_space = !sign ? 1 : 0;
	blank_precision = f_mod->precision > (str_len - sign) ?
		f_mod->precision - str_len + sign : 0;
	blank_width = f_mod->width > (blank_precision + str_len + plus_or_space) ?
		f_mod->width - blank_precision - str_len - plus_or_space : 0;
	fill_char = ' ';
	prnt_cnt = 0;
	if (f_mod->zero && !f_mod->dot)
	{
		fill_char = '0';
		prnt_cnt += print_n_count_sign(&num_char, &str_len, sign);
	}
	prnt_cnt += ft_print_repeat(blank_width, fill_char);
	if (*num_char == '-')
		prnt_cnt += print_n_count_sign(&num_char, &str_len, sign);
	prnt_cnt += print_plus_or_space(f_mod, sign);
	prnt_cnt += ft_print_repeat(blank_precision, '0');
	prnt_cnt += write(1, num_char, str_len);
	return (prnt_cnt);
}

int			ft_print_number(va_list ap, t_modifier *f_mod)
{
	t_nums		nums;
	char		*num_char;
	int			str_len;
	int			sign;
	int			prnt_cnt;

	nums.lnum = f_mod->l ? va_arg(ap, long int) : 0;
	nums.num = !f_mod->l ? va_arg(ap, int) : 0;
	num_char = f_mod->l ? ft_itoa(nums.lnum) : ft_itoa(nums.num);
	str_len = ft_strlen(num_char);
	if (f_mod->dot && !f_mod->precision && (!nums.num && !nums.lnum))
		str_len = 0;
	sign = *num_char == '-' ? 1 : 0;
	prnt_cnt = 0;
	if (f_mod->minus)
		prnt_cnt += left_print(f_mod, num_char, str_len, sign);
	else
		prnt_cnt += right_print(f_mod, num_char, str_len, sign);
	free(num_char);
	return (prnt_cnt);
}
