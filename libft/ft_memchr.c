/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:45:13 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/14 15:00:31 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	i;
	size_t			cpt;

	i = ((unsigned char)c);
	cpt = 0;
	while (cpt < n)
	{
		if (((unsigned char *)s)[cpt] == i)
			return (((void *)s) + cpt);
		cpt++;
	}
	return (NULL);
}
