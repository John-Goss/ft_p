/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 13:28:28 by jle-quer          #+#    #+#             */
/*   Updated: 2016/01/22 16:16:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	if (!(new = ft_strnew((size_t)ft_strlen(s1) + (size_t)ft_strlen(s2) + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		new[i] = ((char *)s1)[i];
	while (s2[j])
	{
		new[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
