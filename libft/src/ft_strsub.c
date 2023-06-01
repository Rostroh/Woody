/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 23:07:40 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:45:56 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*to_return;

	i = 0;
	if (s)
	{
		to_return = (char *)malloc(sizeof(char) * len + 1);
		if (to_return != NULL)
		{
			while (i < len)
			{
				to_return[i] = s[start];
				i++;
				start++;
			}
			to_return[i] = 0;
			return (to_return);
		}
	}
	return (NULL);
}
