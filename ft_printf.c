#include "ft_printf.h"

static int	ft_process_flag(const char *fmt, va_list ap, f_mod_struct *f_mod)
{
	if (*fmt == '-')
		f_mod->minus = 1;
	if (*fmt == '.')
		f_mod->dot = 1;
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
	}
	return (0); 
}

static int	ft_process_type(const char *fmt, va_list ap, f_mod_struct *f_mod, int *print_counter)
{
	if (*fmt == 'c')			
		*print_counter += ft_print_char(ap, f_mod);
	if (*fmt == 's')
		*print_counter += ft_print_str(ap, f_mod);
	if (*fmt == 'd' || *fmt == 'i')
		*print_counter += ft_print_number(ap, f_mod);
	if (*fmt == 'u')
		*print_counter += ft_print_unsigned(ap, f_mod);
	return (0);
}

static int	ft_check_flag_or_type(const char character)
{
	char	*specifiers;

	specifiers = "-.*0123456789csdiu";
		while (*specifiers)
		{
			if (*specifiers == character)
				return (1);
			specifiers++;
		}
	return (0);
}

static int	ft_format(const char *fmt, va_list ap, f_mod_struct *f_mod, int *print_counter)
{
	int	fmt_pos;

	fmt_pos = 0;
	ft_init_structure(f_mod);
	while (ft_check_flag_or_type(*fmt))
	{		
		ft_process_flag(fmt, ap, f_mod);
		if (ft_check_type(*fmt))
		{
			ft_process_type(fmt, ap, f_mod, print_counter);
			fmt_pos++;
			break ;
		}				
		fmt++;
		fmt_pos++;
	}			
	return (fmt_pos);
}

static int	ft_process_arg(const char *fmt, va_list ap, f_mod_struct *f_mod, int *print_counter)
{ //FALTA IMPLEMENTAR MANEJO DE ERRORES
	int	fmt_pos;

	fmt_pos = 1; //PARA INCLUIR LA POSICIÓN DEL %
	fmt++; //PARA AVANZAR AL CARACTER QUE ESTÁ DESPUÉS DEL %
	if (*fmt && *fmt == '%')
	{
		write(1, &*fmt, 1);		
		*print_counter += 1;		
		fmt_pos++;
	}
	else if (*fmt && ft_check_flag_or_type(*fmt))		
		fmt_pos += ft_format(fmt, ap, f_mod, print_counter);
	return (fmt_pos);
}

int			ft_printf(const char *fmt, ...)
{
	va_list ap;
	f_mod_struct	*f_mod;    
	int		print_counter;
	
	if (!(f_mod = malloc(sizeof(f_mod_struct))))
		return (-1);
	va_start(ap, fmt);	
	print_counter = 0;
    while (*fmt)
	{		
		if (*fmt == '%')
			fmt += ft_process_arg(&*fmt, ap, f_mod, &print_counter);
		else
		{
			write(1, &*fmt, 1);
			print_counter++;
			fmt++;
		}						
	}
    va_end(ap);
	free(f_mod);
	return (print_counter);
}
