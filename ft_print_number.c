#include "ft_printf.h"

static char	*ft_itoa(int number) //NORMALIZAR Y SEPARAR EN UN ARCHIVO A PARTE
{
	int		number2;
    int		sign;
	int		digits;
	int		i;
	int		j;
	char	*result;

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
	result = malloc(sizeof(char) * (digits + sign + 1)); //COMPROBAR ERROR??
	result[digits + sign] = 0;
	i = 0;
	if (sign)
		result[i++] = '-';
	while (i < digits + sign)
	{
		int tens;

		tens = 1;
		j = 0;
		while (j++ < digits - i + sign - 1)
			tens *= 10;				
		result[i] = ((number2 / tens) % 10) + '0';		
		i++;	
	}
	return (result);
}

int	ft_print_number(va_list ap, f_mod_struct *f_mod)
{
	int		num;
	char	*num_char;
	int		str_len;
	int		prnt_cnt;
	char	fill_char;
	int		before;
	int		after;

	num = va_arg(ap, int);
	num_char = ft_itoa(num);
	str_len = ft_strlen(num_char);	
	if (f_mod->minus)
	{
		before = 0;
		if (f_mod->precision > str_len)
			after = f_mod->width > f_mod->precision ? f_mod->width - f_mod->precision : 0;
		else
			after = f_mod->width > str_len ? f_mod->width - str_len : 0;
		if (after && f_mod->precision >= str_len && *num_char == '-')
			after--;
	}
	else
	{
		if (f_mod->precision > str_len)
			before = f_mod->width > f_mod->precision ? f_mod->width - f_mod->precision : 0;
		else
			before = f_mod->width > str_len ? f_mod->width - str_len : 0;
		if (before && f_mod->precision >= str_len && *num_char == '-')
			before--;
		after = 0;
	}
	prnt_cnt = 0;
	fill_char = ' ';
	if (f_mod->zero && !f_mod->minus)
	{
		fill_char = '0';
		if (*num_char == '-')
		{
			prnt_cnt += write(1, "-", 1);
			num_char++;
			str_len--;						
		}			
	}	
	while (before--)
		prnt_cnt += write(1, &fill_char, 1);
	if (f_mod->precision)
	{
		if (*num_char == '-' && !f_mod->zero)
		{
			prnt_cnt += write(1, "-", 1);
			num_char++;
			str_len--;						
		}
		while (f_mod->precision-- - str_len)
			prnt_cnt += write(1, "0", 1);		
	}
	prnt_cnt += write(1, num_char, str_len);
	while (after--)
		prnt_cnt += write(1, &fill_char, 1);	
	return (prnt_cnt);
}
