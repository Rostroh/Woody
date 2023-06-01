/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:55:29 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/10 20:17:23 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			c_first(t_arg p)
{
	if (check_octal(p) && (ft_atoi(p.str) != 0 || p.point == 1) && \
				(p.point != 1 || p.hash == 1))
		return (1);
	return (0);
}

int			c_second(t_arg p)
{
	if (!(p.point == 1 && p.pres == 0 && p.str && p.str[0] == '0') || \
				p.letter == '%' || p.letter == 'p')
		return (1);
	return (0);
}

int			is_char(char c)
{
	if (c == 'S' || c == 's' || c == 'c' || c == 'C')
		return (1);
	return (0);
}

int			not_printf(t_arg p)
{
	if (!(p.letter == 'C' || p.letter == 'c' || p.letter == 'd' \
				|| p.letter == 'D' || p.letter == 'i' || p.letter == 'S' || \
				p.letter == 's' || p.letter == 'o' || p.letter == 'O' || \
				p.letter == 'x' || p.letter == 'X' || p.letter == 'p' || \
				p.letter == 'u' || p.letter == 'U') && p.point == 1)
		return (1);
	return (0);
}
