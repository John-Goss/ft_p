/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:33:39 by jle-quer          #+#    #+#             */
/*   Updated: 2015/11/30 11:30:50 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int ptr1;
	int ptr2;

	ptr1 = ft_strlen(dest);
	ptr2 = 0;
	while (src[ptr2])
	{
		dest[ptr1] = src[ptr2];
		ptr2++;
		ptr1++;
	}
	dest[ptr1] = '\0';
	return (dest);
}
