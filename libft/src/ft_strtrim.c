/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:09:14 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:32:47 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *s)
{
	while (ft_isspace(*s) == 1)
	{
		s++;
		if (*s == 0)
			return (0);
	}
	return (1);
}

char		*ft_strtrim(char const *s)
{
	int				end;
	int				size;
	char			*str;
	unsigned int	start;

	end = 0;
	if (!(s))
		return (NULL);
	size = ft_strlen(s);
	start = 0;
	if (check(s) == 0)
		return (ft_strnew(1));
	while (ft_isspace(s[start]) == 1)
		start++;
	while (ft_isspace(s[size - 1]) == 1)
	{
		size--;
		end++;
	}
	str = ft_strsub(s, start, ft_strlen(s) - start - end);
	if (str == NULL)
		return (NULL);
	return (str);
}
