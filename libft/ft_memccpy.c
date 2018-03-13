/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:07:59 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/11 11:18:16 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			cpt;
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	cpt = 0;
	while (cpt < n)
	{
		ptr_dst[cpt] = ptr_src[cpt];
		if (ptr_src[cpt] == (unsigned char)c)
			return (&ptr_dst[cpt + 1]);
		cpt++;
	}
	return (NULL);
}
