/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 02:58:18 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/08 13:54:31 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	const char *cpyl;
	const char *cpyb;

	if (*little == 0)
		return ((char *)big);
	cpyl = little;
	while (*big != 0)
	{
		cpyb = big;
		while (*cpyb == *cpyl)
		{
			cpyb++;
			cpyl++;
			if (*cpyl == '\0')
				return ((char *)big);
		}
		cpyl = little;
		big++;
	}
	return (NULL);
}
