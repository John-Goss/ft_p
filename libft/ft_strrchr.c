/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 17:14:45 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/01 17:27:14 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = ft_strlen((char *)s);
	while (((char *)s)[i] != (char)c && i >= 0)
		i--;
	if (((char *)s)[i] == (char)c)
		return (&((char *)s)[i]);
	return (NULL);
}
