/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:46:39 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/17 17:58:06 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*str_cpy(char *src)
{
	int		i;
	int		src_len;
	char	*cpy;

	src_len = ft_strlen(src);
	if (!(cpy = malloc(sizeof(char) * (src_len + 1))))
		return (0);
	cpy[src_len] = 0;
	i = 0;
	while (i < src_len)
	{
		cpy[i] = src[i];
		i++;
	}
	return (cpy);
}

static char	*fill_char_num(long int number2, int sign, int digits)
{
	char	*result;
	int		i;
	int		j;
	int		decimals;
	char	conversion;

	result = malloc(sizeof(char) * (digits + sign + 1));
	result[digits + sign] = 0;
	i = 0;
	if (sign)
		result[i++] = '-';
	while (i < digits + sign)
	{
		decimals = 1;
		j = 0;
		while (j++ < digits - i + sign - 1)
			decimals *= 10;
		conversion = ((number2 / decimals) % 10) + '0';
		result[i] = conversion;
		i++;
	}
	return (result);
}

char		*ft_itoa(long int number)
{
	long int	number2;
	int			sign;
	int			digits;

	if (!number)
		return (str_cpy("0"));
	number2 = number;
	sign = 0;
	if (number < 0)
	{
		number *= -1;
		number2 *= -1;
		sign = 1;
	}
	digits = 0;
	while (number >= 1)
	{
		number = number / 10;
		digits++;
	}
	return (fill_char_num(number2, sign, digits));
}
