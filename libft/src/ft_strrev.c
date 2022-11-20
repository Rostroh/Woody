/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:49:46 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:31:15 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char const *s)
{
	int		len;
	char	*str;
	char	*cpy;

	len = ft_strlen(s);
	str = ft_strnew(len);
	cpy = str;
	while (len > 0)
	{
		*str = s[len - 1];
		str++;
		len--;
	}
	*str = 0;
	return (cpy);
}
