/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 17:36:41 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/10 20:03:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t		*gestion_wild(char c, va_list ap)
{
	if (c == 'C')
		return (wchar_to_pointer(va_arg(ap, wchar_t)));
	if (c == 'S')
		return (va_arg(ap, wchar_t *));
	return (NULL);
}

t_arg		conv_char(t_arg p)
{
	if (p.letter == 'c' && (p.conv == 2 || p.conv == 3))
		p.letter = 'C';
	if (p.letter == 's' && (p.conv == 2 || p.conv == 3))
		p.letter = 'S';
	return (p);
}

int			nb_wchar(t_arg p)
{
	int			nb;
	wchar_t		*tmp;

	nb = 0;
	tmp = p.wstr;
	while (octect_value(*tmp) + nb <= p.pres)
	{
		nb += octect_value(*tmp);
		tmp++;
	}
	return (nb);
}

int			get_params2(const char ***format, va_list ap, t_arg params)
{
	int		get_printed;

	get_printed = 0;
	params.conv = get_conv(**format);
	if (params.conv != 0)
		(**format) += params.conv % 2 + 1;
	params.letter = ***format;
	params = conv_char(params);
	if (params.letter == 'C' || params.letter == 'S')
		params.wstr = gestion_wild(params.letter, ap);
	else
	{
		params.str = get_string(params, ap);
		if (!params.str && params.letter == 's' && params.point == 0)
		{
			ft_putstr("(null)");
			return (6);
		}
		if (params.str && ft_atoi(params.str) < 0)
			params.pos = 0;
	}
	get_printed = print_shit(params);
	if (params.str && params.letter != 's')
		free(params.str);
	return (get_printed);
}

int			get_params(const char **format, va_list ap)
{
	t_arg		params;

	params = init_struct();
	while (**format == '-' && !ft_isdigit(*(*format + 1)))
	{
		(*format)++;
		params.neg = 1;
		params.brt = 0;
	}
	params = set_struct(format, params);
	params.space = ft_atoi(*format);
	if (params.space != 0)
		*format += len_base(params.space, 10) + more_shit(*format);
	if (**format == '.')
	{
		(*format)++;
		params.point = 1;
		params.pres = ft_atoi(*format);
		if (ft_isdigit(**format))
			*format += len_base(params.pres, 10);
	}
	return (get_params2(&format, ap, params));
}
