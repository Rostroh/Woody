/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maskbit4printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 14:26:48 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/11 11:43:38 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"

char	*put_in(char *str, char *mask)
{
	int		i;
	int		j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(mask) - 1;
	while (j >= 0)
	{
		if (i >= 0 && mask[j] == 'x')
		{
			mask[j] = str[i];
			i--;
		}
		if (mask[j] == 'x')
			mask[j] = '0';
		j--;
	}
	return (mask);
}

int		put_little(char *str)
{
	char			*mask;
	unsigned char	octect;

	mask = ft_strnew(16);
	mask = ft_strcpy(mask, "110xxxxx10xxxxxx");
	mask = put_in(str, mask);
	str = ft_strsub(mask, 0, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	str = ft_strsub(mask, 8, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	free(mask);
	return (2);
}

int		put_short(char *str)
{
	char			*mask;
	unsigned char	octect;

	mask = ft_strnew(24);
	mask = ft_strcpy(mask, "1110xxxx10xxxxxx10xxxxxx");
	mask = put_in(str, mask);
	str = ft_strsub(mask, 0, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	str = ft_strsub(mask, 8, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	str = ft_strsub(mask, 16, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	free(mask);
	return (3);
}

int		put_big(char *str)
{
	char			*mask;
	unsigned char	octect;

	mask = ft_strnew(32);
	mask = ft_strcpy(mask, "11110xxx10xxxxxx10xxxxxx10xxxxxxx");
	mask = put_in(str, mask);
	str = ft_strsub(mask, 0, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	str = ft_strsub(mask, 8, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	str = ft_strsub(mask, 16, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	str = ft_strsub(mask, 24, 8);
	octect = binary_to_decimal(str);
	write(1, &octect, 1);
	free(mask);
	return (4);
}

int		put_fat(wchar_t c)
{
	unsigned char	octect;

	octect = c >> 16;
	write(1, &octect, 1);
	octect = (c << 16) >> 24;
	write(1, &octect, 1);
	octect = (c << 24) >> 24;
	write(1, &octect, 1);
	return (5);
}
