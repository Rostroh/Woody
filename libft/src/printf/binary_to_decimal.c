/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_to_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:45:53 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/04 17:35:35 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int		ft_pow(int nb, int pow)
{
	if (pow == 0)
		return (1);
	if (pow == 1)
		return (nb);
	else
		return (nb * ft_pow(nb, pow - 1));
}

int		binary_to_decimal(char *str)
{
	int		i;
	int		to_return;

	i = 0;
	to_return = 0;
	str = ft_strrev(str);
	while (str[i])
	{
		to_return += (str[i] - 48) * ft_pow(2, i);
		i++;
	}
	free(str);
	return (to_return);
}
