/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_shitty_fonction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 20:32:50 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/10 19:59:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_int_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_int_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

int		check_shit1(t_arg p)
{
	if (p.str)
	{
		if (!(p.point == 1 && p.pres == 0 && p.str[0] == '0'))
			return (0);
		return (1);
	}
	return (-1);
}

int		check_shit2(t_arg p)
{
	if (p.wstr)
	{
		if (!(p.point == 1 && p.pres == 0 && p.wstr[0] == 0))
			return (0);
		return (1);
	}
	return (-1);
}

char	*gestion_pointer(unsigned long p, int point)
{
	char	*str;
	char	*to_return;

	if (point == 1 && p == 0)
	{
		str = ft_strnew(2);
		str = ft_strcpy(str, "0x");
		return (str);
	}
	if (p == 0)
	{
		str = ft_strnew(3);
		str = ft_strcpy(str, "0x0");
		return (str);
	}
	str = unsigned_get_base(p, 16, 'a');
	to_return = ft_strjoin("0x", str);
	free(str);
	return (to_return);
}
