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

int		        ft_check_type(char c);
int		        ft_strlen(char *str);
void            ft_init_structure(f_mod_struct *f_mod);
int             ft_is_digit(int c);
int             ft_add_width(int width, char addition);
int             ft_print_number(va_list ap, f_mod_struct *f_mod);
int	            ft_print_str(va_list ap, f_mod_struct *f_mod);
int             ft_print_char(va_list ap, f_mod_struct *f_mod);
int             ft_printf(const char *fmt, ...);

#endif
