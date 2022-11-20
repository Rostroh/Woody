/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:07:03 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/11 10:44:25 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_shit3(t_arg p)
{
	int		get_printed;

	get_printed = 0;
	if (c_first(p) == 1)
	{
		if (p.pres < (int)ft_strlen(p.str))
		{
			get_printed++;
			ft_putchar('0');
		}
	}
	if (p.zero == ' ' && p.neg == 1)
	{
		ft_putchar('-');
		get_printed++;
	}
	return (get_printed);
}

int		print_shit2(t_arg p)
{
	int		get_printed;

	get_printed = 0;
	if (check_hexa(p) && p.zero == '0')
		get_printed += stupid_shit(p);
	if (check_decimal(p.letter) == 1 && p.pos == 1 && p.zero == '0')
		ft_putchar('+');
	if (p.brt == 1 && (p.letter == 'd' || p.letter == 'i' || p.letter == 'D'))
	{
		ft_putchar(' ');
		get_printed++;
	}
	if (p.zero == '0' && p.neg == 1)
	{
		ft_putchar('-');
		get_printed++;
	}
	return (get_printed);
}

int		call_shit(t_arg p, int tmp)
{
	int		get_printed;

	get_printed = 0;
	get_printed += print_shit2(p);
	if (tmp > 0)
		get_printed += put_shit(nb_space(p), p.zero);
	get_printed += print_shit3(p);
	if (check_decimal(p.letter) == 1 && p.pos == 1 && p.zero != '0')
		ft_putchar('+');
	if (check_hexa(p) && p.zero == ' ')
		get_printed += stupid_shit(p);
	return (get_printed);
}

int		print_shit(t_arg p)
{
	int		tmp;
	int		get_printed;

	if (p.letter == 'p')
		return (print_pointer(p));
	get_printed = 0;
	if (p.letter != 'C' && p.letter != 'S' && p.str)
		p = set_params(p);
	tmp = p.space;
	if (p.space < 0)
		p.space = -p.space;
	get_printed += call_shit(p, tmp);
	if (p.letter != 'C')
		get_printed += put_shit(nb_pres(p), '0');
	if (c_second(p) == 1)
		get_printed += print(p, 0);
	if (tmp < 0)
		get_printed += put_shit(nb_space(p), p.zero);
	if (p.wstr && p.letter != 'S')
		free(p.wstr);
	if (!(p.letter == 'i' || p.letter == 'd' || p.letter == 'D'))
		p.pos = 0;
	return (get_printed + p.pos);
}
