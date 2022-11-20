/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 22:21:45 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:27:06 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*to_return;

	if (!(s1 && s2))
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str != NULL)
	{
		to_return = str;
		while (*s1 != 0)
		{
			*str = *s1;
			str++;
			s1++;
		}
		while (*s2 != 0)
		{
			*str = *s2;
			str++;
			s2++;
		}
		*str = 0;
		return (to_return);
	}
	return (NULL);
}
