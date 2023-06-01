/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:46:59 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/10 16:47:12 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			gestion_string(t_arg p)
{
	int		value;

	value = 0;
	if (p.letter == 'S')
	{
		if (ft_wstrlen(p.wstr) == 0)
			return (0);
		if (p.pres < (int)ft_wstrlen(p.wstr) && p.pres > 0)
			value = nb_wchar(p);
		else
			value = ft_wstrlen(p.wstr);
	}
	if (p.letter == 's')
	{
		if (ft_strlen(p.str) == 0)
			return (0);
		if (p.pres < (int)ft_strlen(p.str) && p.pres > 0)
			value = p.pres;
		else
			value = ft_strlen(p.str);
	}
	return (value);
}

int			get_value(t_arg p)
{
	int		value;

	value = 0;
	if (p.point == 1 && p.pres == 0 && (p.letter == 's' || p.letter == 'S'))
		return (0);
	if (p.letter == 'c' && p.cha == 0)
		return (1);
	if (p.letter == 's' || p.letter == 'S')
		return (gestion_string(p));
	else
	{
		if (p.str)
			value = (int)ft_strlen(p.str);
		if (p.wstr)
			value = p.pres != 0 ? p.pres : (int)ft_wstrlen(p.wstr);
	}
	if ((p.letter == 'X' || p.letter == 'x') && (p.hash == 1))
		value += ft_atoi(p.str) != 0 ? 2 : 0;
	return (value);
}

int			fuck_me(t_arg p, int to_print)
{
	to_print -= p.pos;
	to_print -= p.neg;
	return (to_print);
}

int			nb_space(t_arg p)
{
	int		i;
	int		to_print;

	i = 0;
	if (not_printf(p) == 1)
		return (p.space - 1);
	if (p.space < 0)
		p.space = -p.space;
	if (p.point == 1 && p.pres == 0 && p.letter != '%' && p.letter != 'c')
		return (p.space);
	to_print = p.space - get_value(p);
	if (is_char(p.letter) == 0)
		to_print -= p.pres > (int)ft_strlen(p.str) ? p.pres - get_value(p) : 0;
	if (check_decimal(p.letter))
		to_print = fuck_me(p, to_print);
	if (check_octal(p) == 1)
		to_print -= 1;
	if (p.str)
		i = p.pres > (int)ft_strlen(p.str) ? 0 : p.pres - ft_strlen(p.str);
	if (p.wstr)
		i = p.pres > (int)ft_wstrlen(p.wstr) ? 0 : p.pres - ft_wstrlen(p.wstr);
	if (i < 0 || is_char(p.letter) == 1)
		i = 0;
	to_print = to_print - i - p.brt;
	return (to_print > 0 ? to_print : 0);
}
