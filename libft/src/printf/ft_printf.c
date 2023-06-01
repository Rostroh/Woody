/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 13:48:02 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/05 17:32:13 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_arg		init_struct(void)
{
	t_arg		params;

	params.neg = 0;
	params.cha = 0;
	params.pos = 0;
	params.brt = 0;
	params.str = NULL;
	params.wstr = NULL;
	params.hash = 0;
	params.conv = 0;
	params.pres = 0;
	params.zero = ' ';
	params.point = 0;
	params.space = 0;
	params.letter = ' ';
	return (params);
}

t_arg		set_struct(const char **format, t_arg params)
{
	if (**format == '#')
	{
		(*format)++;
		params.hash = 1;
		return (set_struct(format, params));
	}
	if (**format == ' ')
	{
		(*format)++;
		params.brt = 1;
		return (set_struct(format, params));
	}
	if (**format == '+')
	{
		(*format)++;
		params.pos = 1;
		return (set_struct(format, params));
	}
	if (**format == '0')
	{
		(*format)++;
		params.zero = '0';
		return (set_struct(format, params));
	}
	return (params);
}

int			get_conv(const char *format)
{
	int		i;
	int		j;

	i = 1;
	j = 3;
	if (*format == 'j')
		return (6);
	if (*format == 'z')
		return (8);
	while (*format == 'l')
	{
		format++;
		i++;
	}
	if (i != 1)
		return (i);
	while (*format == 'h')
	{
		format++;
		j++;
	}
	if (j != 3)
		return (j);
	return (0);
}

int			more_shit(const char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == '+' || *str == '-')
		{
			str++;
			while (*str && *str == '0')
			{
				i++;
				str++;
			}
		}
		str++;
	}
	return (i);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			get_print;

	get_print = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		while (*format != '%' && *format)
		{
			ft_putchar(*format++);
			get_print++;
		}
		if (*format == '%' && *(format + 1))
		{
			format++;
			get_print += get_params((&format), ap);
			format++;
		}
		if (*format == '%' && !(*(format + 1)))
			return (get_print);
	}
	va_end(ap);
	return (get_print);
}
