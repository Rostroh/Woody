/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:41:23 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:27:51 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*to_return;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		to_return = (char *)malloc(sizeof(char) * len + 1);
		if (to_return != NULL)
		{
			while (i < len)
			{
				to_return[i] = f(i, *s);
				i++;
				s++;
			}
			to_return[i] = 0;
			return (to_return);
		}
	}
	return (NULL);
}
