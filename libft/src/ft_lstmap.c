/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 19:05:42 by rostroh           #+#    #+#             */
/*   Updated: 2016/11/12 12:49:20 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*cpy;

	begin = NULL;
	if (lst)
	{
		cpy = (t_list *)malloc(sizeof(t_list) * 1);
		cpy = f(lst);
		begin = cpy;
		while (lst->next)
		{
			cpy->next = (t_list *)malloc(sizeof(t_list) * 1);
			cpy->next = f(lst->next);
			lst = lst->next;
			cpy = cpy->next;
		}
		free(cpy);
	}
	return (begin);
}
