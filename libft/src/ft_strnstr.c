/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:41:10 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:44:42 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*cpyl;
	const char	*cpyb;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	cpyl = little;
	while (*big != 0 && i < len)
	{
		j = i;
		cpyb = big;
		while (*cpyb == *cpyl && j++ < len)
		{
			cpyb++;
			cpyl++;
			if (*cpyl == '\0')
				return ((char *)big);
		}
		i++;
		big++;
		cpyl = little;
	}
	return (NULL);
}
