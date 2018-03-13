/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:53:18 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/14 15:06:43 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s2_len;
	size_t	i;
	char	*ptr;

	s2_len = ft_strlen(s2);
	ptr = (char *)s1;
	if (ft_strlen(ptr) < s2_len)
		return (NULL);
	if (!s2)
		return (ptr);
	if (s2_len > len)
		return (NULL);
	i = len - s2_len + 1;
	while (i > 0)
	{
		if (ft_strncmp(ptr, s2, s2_len) == 0)
			return (ptr);
		ptr++;
		i--;
	}
	return (NULL);
}
