/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:10:39 by jle-quer          #+#    #+#             */
/*   Updated: 2015/11/30 17:43:47 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t cpt;

	cpt = 0;
	if (src == dst)
		return (dst);
	else if (src < dst)
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
	else if (src > dst)
		while (cpt < len)
		{
			((char *)dst)[cpt] = ((char *)src)[cpt];
			cpt++;
		}
	return (dst);
}
