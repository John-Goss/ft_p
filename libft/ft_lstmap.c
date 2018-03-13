/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:00:46 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/07 16:34:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*new;

	begin = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		if (!begin)
		{
			begin = (f)(lst);
			lst = lst->next;
			new = begin;
		}
		else
		{
			new->next = (f)(lst);
			new = new->next;
			lst = lst->next;
		}
	}
	return (begin);
}
