/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 13:07:19 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 20:05:43 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*set_moins_d_2(t_struct *strct, char *str, long long n, char *larg)
{
	char *new;

	if (strct->plus == 1 && n >= 0)
		str = set_d_plus_space(str, '+');
	if (strct->space == 1 && n >= 0 && strct->larg < (int)ft_strlen(str))
		str = set_d_plus_space(str, ' ');
	new = ft_strjoin(str, larg);
	return (new);
}
