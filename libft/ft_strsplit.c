/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:51:06 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/11 16:53:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	char	**new;
	size_t	start;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (new == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i != start)
			new[j++] = ft_strsub(s, start, (i - start));
	}
	new[j] = NULL;
	return (new);
}
