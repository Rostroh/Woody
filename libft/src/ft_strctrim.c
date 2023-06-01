/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 22:34:17 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:23:32 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *s, char c)
{
	while (*s == c)
	{
		s++;
		if (*s == 0)
			return (0);
	}
	return (1);
}

char		*ft_strctrim(char const *s, char c)
{
	int				end;
	int				size;
	char			*str;
	unsigned int	start;

	end = 0;
	size = ft_strlen(s);
	start = 0;
	if (!s || !c)
		return (NULL);
	if (check(s, c) == 0)
		return (ft_strnew(1));
	while (s[start] == c)
		start++;
	while (s[size - 1] == c)
	{
		size--;
		end++;
	}
	str = ft_strsub(s, start, ft_strlen(s) - start - end);
	return (str);
}
