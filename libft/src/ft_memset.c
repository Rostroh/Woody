/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:45:49 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:45:17 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	void	*to_return;

	i = 0;
	to_return = b;
	while (i < len)
	{
		*(unsigned char*)b = c;
		i++;
		b++;
	}
	return (to_return);
}
