/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:42:44 by onapoli-          #+#    #+#             */
/*   Updated: 2020/08/24 18:11:03 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_modifier
{
	int minus;
	int width;
	int zero;
	int dot;
	int precision;
	int	asterisk;
}				t_modifier;

char			*ft_itox(unsigned long input, char hex_type);
char			*ft_itoa(long int number);
void			handle_print_no_flags_no_mods(char fmt_char,
int *print_counter);
void			process_flag_digit_or_asterisk(char fmt_char, t_modifier *f_mod,
va_list ap);
int				ft_print_repeat(int i, char c);
int				ft_strlen(char *str);
void			ft_init_structure(t_modifier *f_mod);
int				ft_is_digit(int c);
int				ft_add_number(int number, char addition);
int				ft_print_empty(t_modifier *f_mod, int next_char);
int				ft_print_percent(t_modifier *f_mod);
int				ft_print_pointer(va_list ap, t_modifier *f_mod);
int				ft_print_hex(va_list ap, t_modifier *f_mod, char hex_type);
int				ft_print_unsigned(va_list ap, t_modifier *f_mod);
int				ft_print_number(va_list ap, t_modifier *f_mod);
int				ft_print_str(va_list ap, t_modifier *f_mod);
int				ft_print_char(va_list ap, t_modifier *f_mod);
int				ft_printf(const char *fmt, ...);

#endif
