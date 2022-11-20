/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:59:50 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:47:56 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;
	char	*cpy;

	i = 0;
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str != NULL)
	{
		cpy = str;
		while (i < size)
		{
			*str = 0;
			str++;
			i++;
		}
		*str = 0;
		return (cpy);
	}
	return (NULL);
}
