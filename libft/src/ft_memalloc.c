/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:45:58 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:46:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*b;

	i = 0;
	b = (char *)malloc(sizeof(char) * size);
	if (b != NULL)
	{
		while (i < size)
		{
			b[i] = 0;
			i++;
		}
		return ((void *)b);
	}
	return (NULL);
}
