/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:41:56 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/07 11:39:08 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while (i <= j && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (j >= i && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	len = j - i + 1;
	new = ft_strsub(s, i, len);
	return (new);
}
