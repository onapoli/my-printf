/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <onapoli-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:45:39 by onapoli-          #+#    #+#             */
/*   Updated: 2020/05/29 15:46:10 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_unit_hex_converter(unsigned int u, char hex_type)
{
	if (u < 10)
        return (u + '0');
	else if (hex_type == 'X')
		return (u + 55);
    else
		return (u + 87);
}

static void	hex_constructor(unsigned long input, char **hex_char, int hex_len, char hex_type)
{
	unsigned long	h;
	int				i;

	i = 1;
	while (hex_len--)
	{
		int j;

		h = input;
		j = hex_len;
		while (j--)
			h /= 16;
		h %= 16;
		(*hex_char)[i++] = ft_unit_hex_converter(h, hex_type);
	}
}

char		*ft_itox(unsigned long input, char hex_type)
{
    unsigned long		h;
	char				*hex_char;	
    int     			hex_len;

	h = input;
    hex_len = 0;
    while(h >= 16)
    {
        h /= 16;
        hex_len++;
    }
	if (!(hex_char = malloc(sizeof(char) * (hex_len + 1))))
		return (0);
	hex_char[hex_len] = 0;
	hex_char[0] = ft_unit_hex_converter(h, hex_type);
	hex_constructor(input, &hex_char, hex_len, hex_type);	
	return (hex_char);
}