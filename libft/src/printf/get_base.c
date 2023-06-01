/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 12:58:01 by rostroh           #+#    #+#             */
/*   Updated: 2017/02/08 14:13:39 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		len_base(long nb, int base)
{
	int		len;

	len = 1;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb >= base)
	{
		len++;
		nb /= base;
	}
	return (len);
}

int		len_unsigned_base(unsigned long nb, int base)
{
	int		len;

	len = 1;
	while (nb >= (unsigned long)base)
	{
		len++;
		nb /= base;
	}
	return (len);
}

char	*get_tab(int base, char c)
{
	int		i;
	char	*tab;

	i = 0;
	tab = (char*)malloc(sizeof(char) * base + 1);
	if (tab)
	{
		while (i < base)
		{
			if (i < 10)
				tab[i] = i + 48;
			else
				tab[i] = c++;
			i++;
		}
		tab[i] = '\0';
		return (tab);
	}
	return (NULL);
}

char	*get_base(long nb, int base, char c)
{
	int		len;
	char	*tab;
	char	*str;

	len = 0;
	if (base > 36 || base < 2)
		return (NULL);
	if (base == 10 && nb < 0)
		return (ft_long_itoa(nb));
	tab = get_tab(base, c);
	len = len_base(nb, base);
	str = ft_strnew(len);
	str[len--] = '\0';
	while (len > 0)
	{
		str[len] = tab[nb % base];
		nb /= base;
		len--;
	}
	str[len] = tab[nb];
	free(tab);
	return (str);
}

char	*unsigned_get_base(unsigned long nb, int base, char c)
{
	int		len;
	char	*tab;
	char	*str;

	len = 0;
	if (base > 36 || base < 2)
		return (NULL);
	tab = get_tab(base, c);
	len = len_unsigned_base(nb, base);
	str = ft_strnew(len);
	str[len--] = '\0';
	while (len > 0)
	{
		str[len] = tab[nb % base];
		nb /= base;
		len--;
	}
	str[len] = tab[nb];
	free(tab);
	return (str);
}
