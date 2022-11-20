/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:25:36 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:23:52 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *to_return;

	to_return = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (to_return != NULL)
	{
		to_return = ft_strcpy(to_return, s1);
		to_return[ft_strlen(s1)] = '\0';
	}
	return (to_return);
}
