/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 17:46:46 by jle-quer          #+#    #+#             */
/*   Updated: 2016/06/07 17:46:48 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushfront(t_list **blst, void const *content, size_t content_size)
{
	t_list	*list;

	list = *blst;
	if (list)
	{
		list = ft_lstnew(content, content_size);
		list->next = *blst;
		*blst = list;
	}
	else
		*blst = ft_lstnew(content, content_size);
}
