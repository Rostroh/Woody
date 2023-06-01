/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 00:18:02 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:17:46 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		nb;
	int		ope;

	nb = 0;
	ope = 1;
	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		ope = 44 - *str;
		str++;
	}
	while (ft_isdigit(*str) == 1 && *str != 0)
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb * ope);
}
