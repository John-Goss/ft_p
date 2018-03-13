/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 12:46:27 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/07 17:08:16 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;
	t_list *next;

	ptr = *alst;
	while (ptr)
	{
		next = ptr->next;
		del(ptr->content, ptr->content_size);
		free(ptr);
		ptr = next;
	}
	*alst = NULL;
}
