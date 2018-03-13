/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:47:45 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/11 11:03:50 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	cpt;
	int		i;
	int		j;

	j = ft_strlen(s1);
	i = 0;
	cpt = 0;
	while (s2[i] && cpt < n)
	{
		s1[j] = ((char *)s2)[i];
		i++;
		j++;
		cpt++;
	}
	s1[j] = '\0';
	return (s1);
}
