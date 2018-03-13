/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 12:43:31 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 17:06:27 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*set(t_struct *form)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(form->larg - 1);
	while (i < form->larg - 1)
		str[i++] = ' ';
	str[form->larg - 1] = '\0';
	return (str);
}

char			*set_tag(t_struct *form)
{
	char	*str;
	char	*larg;

	larg = NULL;
	if (form->larg > 1)
		larg = set(form);
	if (form->moins == 1)
		str = ft_strjoin("%", larg);
	else
		str = ft_strjoin(larg, "%");
	g_ret += (int)ft_strlen(str);
	free(larg);
	return (str);
}
