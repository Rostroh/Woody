/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_fonction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 00:34:48 by rostroh           #+#    #+#             */
/*   Updated: 2022/06/15 11:57:21 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			octect_value(wchar_t c)
{
	int		res;
	char	*str;

	res = 0;
	str = get_base((unsigned int)c, 2, '.');
	if (ft_strlen(str) <= 7)
		res = 1;
	else if (ft_strlen(str) <= 11)
		res = 2;
	else if (ft_strlen(str) <= 16)
		res = 3;
	else if (ft_strlen(str) <= 21)
		res = 4;
	else
		res = 5;
	free(str);
	return (res);
}

size_t		ft_wstrlen(wchar_t *wstr)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (!wstr)
		return (0);
	while (wstr[i] != '\0')
	{
		res += octect_value(wstr[i]);
		i++;
	}
	return (res);
}

wchar_t		*wchar_to_pointer(wchar_t w)
{
	wchar_t		*wstr;

	wstr = (wchar_t *)malloc(sizeof(wchar_t) * 2);
	if (!wstr)
		return (NULL);
	*wstr = w;
	wstr[1] = '\0';
	return (wstr);
}

int			ft_putwstr(wchar_t *wstr, char l)
{
	int		printed;

	printed = 0;
	if (l == 'C' && *wstr == '\0')
		return (1);
	if (!wstr)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (*wstr != '\0')
	{
		printed += ft_putwchar(*wstr);
		wstr++;
	}
	return (printed);
}

int			ft_putwchar(wchar_t c)
{
	int			get;
	char		*str;

	get = 0;
	str = get_base((unsigned int)c, 2, '.');
	if (ft_strlen(str) <= 7)
		get = ft_int_putchar(c);
	else if (ft_strlen(str) <= 11)
		get = put_little(str);
	else if (ft_strlen(str) <= 16)
		get = put_short(str);
	else if (ft_strlen(str) <= 21)
		get = put_big(str);
	else if (ft_strlen(str) <= 26)
		get = put_fat(c);
	free(str);
	return (get);
}
