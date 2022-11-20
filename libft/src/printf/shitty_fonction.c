/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shitty_fonction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 15:32:00 by rostroh           #+#    #+#             */
/*   Updated: 2022/06/15 11:56:39 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_shit(int nb, char c)
{
	int		i;

	i = 0;
	while (i++ < nb)
		ft_putchar(c);
	return (nb);
}

int		nb_pres(t_arg p)
{
	int		to_print;

	to_print = 0;
	if (p.letter == 's' || p.letter == 'c')
		return (0);
	if (p.str)
		to_print = p.pres - (int)ft_strlen(p.str);
	if (p.wstr)
		to_print = p.pres - (int)ft_wstrlen(p.wstr);
	return (to_print > 0 ? to_print : 0);
}

char	*char_to_pointer(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	*str = c;
	str[1] = '\0';
	return (str);
}

char	*abs_string(char *str)
{
	char	*cpy;
	char	*to_return;

	to_return = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!to_return)
		return (NULL);
	cpy = to_return;
	if (*str == '-')
		str++;
	while (*str)
	{
		*cpy = *str;
		str++;
		cpy++;
	}
	*cpy = '\0';
	return (to_return);
}
