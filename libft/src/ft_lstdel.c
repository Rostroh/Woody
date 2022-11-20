/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:15:25 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:18:50 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		**begin;
	t_list		*list;

	begin = alst;
	list = *alst;
	if (list)
	{
		while (list->next)
		{
			del(list->content, list->content_size);
			free(*alst);
			*alst = NULL;
			list = list->next;
		}
		del(list->content, list->content_size);
		free(*alst);
		free(list);
		*alst = NULL;
		*begin = NULL;
	}
}
