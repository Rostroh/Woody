/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:09:14 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/10 11:57:08 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		stupid_shit(t_arg params)
{
	if (params.hash == 1 && ft_atoi(params.str) != 0)
	{
		ft_putchar('0');
		ft_putchar(params.letter);
		return (2);
	}
	return (0);
}

int		help_wchar(t_arg p, int i)
{
	wchar_t *tmp;

	tmp = p.wstr;
	while (i < p.pres)
	{
		if (octect_value(*tmp) + i <= p.pres)
		{
			ft_putwchar(*tmp);
			i += octect_value(*tmp);
			tmp++;
		}
		else
			return (i);
	}
	return (p.pres);
}

int		print(t_arg p, int i)
{
	char	*cpy;

	if (p.point == 1 && p.pres == 0 && (p.letter == 's' || p.letter == 'S'))
		return (0);
	if (p.letter == 'c')
		return (ft_int_putchar(p.cha));
	if (p.letter == 's' && p.pres < (int)ft_strlen(p.str) && p.pres > 0)
	{
		cpy = p.str;
		while (i++ < p.pres)
			ft_putchar(*cpy++);
		return (p.pres);
	}
	if (p.letter == 'S' && p.pres < (int)ft_wstrlen(p.wstr) && p.pres > 0)
		return (help_wchar(p, i));
	else if (p.letter == 'C' || p.letter == 'S')
		return (ft_putwstr(p.wstr, p.letter));
	else
		return (ft_int_putstr(p.str));
}

int		print_pointer(t_arg p)
{
	int		tmp;
	int		get_printed;
	char	*cpy;

	tmp = p.space;
	cpy = p.str;
	get_printed = 0;
	if (p.space < 0)
		p.space = -p.space;
	p.space = p.space >= 2 ? p.space - 2 : p.space;
	if (tmp > 0 && p.zero == ' ')
		get_printed += put_shit(nb_space(p), ' ');
	ft_putstr("0x");
	if (p.point == 1 && *cpy == '0' && p.pres == 0)
		return (get_printed + 2);
	if (tmp > 0 && p.zero == '0')
		get_printed += put_shit(nb_space(p), '0');
	get_printed += put_shit(nb_pres(p), '0');
	get_printed += (int)ft_strlen(p.str) + 2;
	ft_putstr(p.str);
	if (tmp < 0)
		get_printed += put_shit(nb_space(p), ' ');
	return (get_printed);
}
