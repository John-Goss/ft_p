/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:22:27 by jle-quer          #+#    #+#             */
/*   Updated: 2015/12/04 14:52:44 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t cpt;

	cpt = 0;
	if (!n)
		return (0);
	while (s1[cpt] && s2[cpt] && s1[cpt] == s2[cpt] && cpt < n)
		cpt++;
	if (cpt == n)
		return (0);
	return ((unsigned char)s1[cpt] - (unsigned char)s2[cpt]);
}
