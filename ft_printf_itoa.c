#include "ft_printf.h"

static char *fill_char_num(long int number2, int sign, int digits)
{
    char *result;
    int i;
    int j;

    result = malloc(sizeof(char) * (digits + sign + 1)); //COMPROBAR ERROR??
	result[digits + sign] = 0;
    i = 0;
    if (sign)
		result[i++] = '-';    
	while (i < digits + sign)
	{
		int decimals;
        char conversion;

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

char        *ft_itoa(long int number)
{
	long int	number2;
    int			sign;
	int			digits;

	if (!number)
		return ("0");
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