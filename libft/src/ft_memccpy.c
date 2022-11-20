/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:33:07 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:47:14 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(char *)src == c)
		{
			*(char *)dst = c;
			dst++;
			return (dst);
		}
		*(char *)dst = *(char *)src;
		i++;
		dst++;
		src++;
	}
	return (NULL);
}
