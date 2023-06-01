/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 20:59:29 by rostroh           #+#    #+#             */
/*   Updated: 2017/01/29 16:54:03 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	lennb(long n)
{
	int		len;

	len = 1;
	n = n < 0 ? -n : n;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*bis(long n)
{
	int		i;
	int		len;
	char	*to_return;

	len = lennb(n);
	to_return = (char *)malloc(sizeof(char) * len + (n < 0 ? 2 : 1));
	if (to_return != NULL)
	{
		if (n < 0)
		{
			n = -n;
			to_return[0] = '-';
			len++;
		}
		i = len - 1;
		while (n > 9)
		{
			to_return[i--] = n % 10 + '0';
			n /= 10;
		}
		if (n < 10)
			to_return[i] = n + '0';
		to_return[len] = 0;
	}
	return (to_return);
}

char		*ft_long_itoa(long n)
{
	char	*str;

	if (n < -9223372036854775807)
	{
		str = malloc(sizeof(char) * 11);
		if (str != NULL)
		{
			str = ft_strcpy(str, "-92233720368547758078");
			return (str);
		}
	}
	else
		return (bis(n));
	return (NULL);
}
