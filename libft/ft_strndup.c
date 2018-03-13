/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 16:52:42 by jle-quer          #+#    #+#             */
/*   Updated: 2016/05/12 17:07:27 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t length)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!s1 || length == 0)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * length + 1)))
		return (NULL);
	while (s1[i] && i < length)
	{
		new[i] = s1[i];
		i++;
	}
	if (!s1[i] && i < length)
		ft_bzero(new + i, (length - i));
	new[length] = '\0';
	return (new);
}
