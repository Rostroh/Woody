/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:57:25 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:31:52 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenword(char const *s, char c)
{
	int		to_return;

	to_return = 0;
	while (*s == c)
		s++;
	while (*s != c && *s != 0)
	{
		to_return++;
		s++;
	}
	return (to_return);
}

static int	countoccurences(char const *s, char c)
{
	int		to_return;

	to_return = s[0] == c ? 0 : 1;
	if (*s == 0)
		return (0);
	while (*s == c)
	{
		s++;
		if (*s == 0)
			return (0);
	}
	while (*s != 0)
	{
		if (*s != c && *(s - 1) == c)
			to_return++;
		s++;
	}
	return (to_return);
}

char		**ft_strsplit(char const *s, char c)
{
	int			i;
	int			nb;
	char		**tab;
	const char	*cpy;

	if (s != NULL && c)
	{
		i = 0;
		cpy = s;
		nb = countoccurences(s, c);
		tab = (char **)malloc(sizeof(char*) * nb + 1);
		if (!tab)
			return (NULL);
		while (nb > 0)
		{
			while (*cpy != 0 && *cpy == c)
				cpy++;
			tab[i++] = ft_strsub(s, cpy - s, lenword(cpy, c));
			cpy = cpy + lenword(cpy, c);
			nb--;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
