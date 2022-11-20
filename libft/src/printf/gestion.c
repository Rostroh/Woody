/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 16:57:08 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/10 12:00:29 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		check_decimal(char c)
{
	if (c == 'D' || c == 'd' || c == 'i')
		return (1);
	return (0);
}

int		check_hexa(t_arg p)
{
	if ((p.letter == 'x' || p.letter == 'X') && p.hash == 1)
		return (1);
	return (0);
}

int		check_octal(t_arg p)
{
	if ((p.letter == 'o' || p.letter == 'O') && p.hash == 1)
		return (1);
	return (0);
}

t_arg	just_norm(t_arg p)
{
	if (p.letter == '%')
		p.pres = 0;
	if (p.space < 0)
		p.zero = ' ';
	if (p.letter == 'p' && p.zero == '0')
		p.space *= -1;
	if (p.str)
	{
		if (nb_pres(p) >= (int)ft_strlen(p.str) && ft_strlen(p.str) > 0)
			p.zero = ' ';
		if (ft_strcmp(p.str, "-92233720368547758078") == 0)
		{
			p.neg = 1;
			p.pos = 0;
			p.str = ft_strcpy(p.str, "9223372036854775808");
		}
	}
	return (p);
}

t_arg	set_params(t_arg params)
{
	char	*cpy;

	cpy = params.str;
	params.cha = *cpy;
	if (params.neg == 1 && params.space > 0)
		params.space = -params.space;
	if (params.neg == 1)
		params.zero = ' ';
	if (params.str && ft_atoi(params.str) >= 0)
		params.neg = 0;
	params = just_norm(params);
	if (params.str[0] == '-' && check_decimal(params.letter) == 1)
	{
		params.neg = 1;
		params.pos = 0;
		params.str = abs_string(params.str);
	}
	if (params.pos != 0 || params.neg != 0)
		params.brt = 0;
	if (params.letter == 'c' || params.letter == 's')
	{
		params.neg = 0;
		params.pos = 0;
	}
	return (params);
}
