/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:31:18 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/04 18:43:39 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	cpt;

	cpt = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[cpt] == s2[cpt] && cpt < n - 1 && s1[cpt] && s2[cpt])
		cpt++;
	if (s1[cpt] != s2[cpt] && s2[cpt] && s1[cpt])
		return (0);
	return (1);
}
