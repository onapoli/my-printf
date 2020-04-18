#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct  s_struct
{
    int minus;
    int width;
    int zero;
    int dot;
    int precision;
}               f_mod_struct;

char            *ft_itoa(long int number);
int             ft_print_repeat(int i, char c);
int		        ft_check_type(char c);
int		        ft_strlen(char *str);
void            ft_init_structure(f_mod_struct *f_mod);
int             ft_is_digit(int c);
int             ft_add_number(int number, char addition);
int             ft_print_unsigned(va_list ap, f_mod_struct *f_mod);
int             ft_print_number(va_list ap, f_mod_struct *f_mod);
int	            ft_print_str(va_list ap, f_mod_struct *f_mod);
int             ft_print_char(va_list ap, f_mod_struct *f_mod);
int             ft_printf(const char *fmt, ...);

#endif