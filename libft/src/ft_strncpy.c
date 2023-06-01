/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:00:37 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:37:52 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < (len < ft_strlen(src) ? len : ft_strlen(src)))
	{
		dest[i] = (char)src[i];
		i++;
	}
	if (i < len)
	{
		while (i < len)
		{
			dest[i] = 0;
			i++;
		}
	}
	return (dest);
}
