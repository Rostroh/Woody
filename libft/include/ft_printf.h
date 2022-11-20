/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:02:34 by rostroh           #+#    #+#             */
/*   Updated: 2022/06/15 11:55:19 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdint.h>
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct	s_arg
{
	int			neg;
	char		cha;
	int			pos;
	int			brt;
	int			hash;
	int			conv;
	int			pres;
	char		*str;
	wchar_t		*wstr;
	int			space;
	char		zero;
	int			point;
	char		letter;
}				t_arg;

/*
** file binary_to_decimal.c -- 2 fonctions
*/
int				ft_pow(int nb, int pow);
int				binary_to_decimal(char *str);

/*
** file condition.c -- 4 fonctions
*/
int				is_char(char c);
int				c_first(t_arg p);
int				c_second(t_arg p);
int				not_printf(t_arg p);

/*
** file conv.c -- 5 fonctions
*/
char			*poney3(t_arg param, va_list ap);
char			*poney2(t_arg param, va_list ap);
char			*get_string(t_arg param, va_list ap);
char			*gestion_arg(int arg, int base, char letter, va_list ap);
char			*gestion_arg2(int arg, int base, char letter, va_list ap);

/*
** file ft_printf.c -- 5 fonctions
*/
t_arg			init_struct(void);
int				more_shit(const char *str);
int				get_conv(const char *format);
int				ft_printf(const char *format, ...);
t_arg			set_struct(const char **format, t_arg params);

/*
** file ft_putwchar.c -- 5 fonctions
*/
int				put_fat(wchar_t c);
int				put_big(char *str);
int				put_short(char *str);
int				put_little(char *str);
char			*put_in(char *str, char *mask);

/*
** file gestion.c -- 5 fonctions
*/
t_arg			just_norm(t_arg p);
int				check_hexa(t_arg p);
int				check_octal(t_arg p);
int				check_decimal(char c);
t_arg			set_params(t_arg params);

/*
** file gestion_print.c -- 4 fonctions
*/
int				print_shit(t_arg p);
int				print_shit2(t_arg p);
int				print_shit3(t_arg p);
int				call_shit(t_arg p, int tmp);

/*
** file get_base.c -- 5 fonctions
*/
char			*get_tab(int base, char c);
int				len_base(long nb, int base);
char			*get_base(long nb, int base, char c);
int				len_unsigned_base(unsigned long nb, int base);
char			*unsigned_get_base(unsigned long nb, int base, char c);

/*
** file more_shitty_fonction.c -- 5 fonctions
*/
int				check_shit1(t_arg p);
int				check_shit2(t_arg p);
int				ft_int_putchar(char c);
int				ft_int_putstr(char *str);
char			*gestion_pointeur(unsigned long p, int point);

/*
** file params.c -- 5 fonctions
*/
int				nb_wchar(t_arg p);
t_arg			conv_char(t_arg p);
wchar_t			*gestion_wild(char c, va_list ap);
int				get_params(const char **format, va_list ap);
int				get_params2(const char ***format, va_list ap, t_arg params);

/*
** file print.c -- 4 fonctions
*/
int				print(t_arg p, int i);
int				print_pointer(t_arg p);
int				stupid_shit(t_arg params);
int				help_wchar(t_arg p, int i);

/*
** file shitty_fonction -- 4 fonctions
*/
int				nb_pres(t_arg p);
char			*abs_string(char *str);
int				put_shit(int nb, char c);
char			*char_to_pointer(char c);

/*
** file space.c -- 4 fonctions
*/
int				nb_space(t_arg p);
int				get_value(t_arg p);
int				gestion_string(t_arg p);
int				fuck_me(t_arg p, int to_print);

/*
** file wchar_fonction.c -- 5 fonctions
*/
int				ft_putwchar(wchar_t c);
int				octect_value(wchar_t c);
size_t			ft_wstrlen(wchar_t *str);
wchar_t			*wchar_to_pointer(wchar_t w);
int				ft_putwstr(wchar_t *wstr, char l);

#endif
