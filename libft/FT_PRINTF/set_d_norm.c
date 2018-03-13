/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_d_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 12:52:15 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 16:06:26 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*set_moins_d_norm_2(t_struct *form, char *str, char *larg,
		long long n)
{
	char	*new;

	if (form->plus == 1 && n >= 0)
		str = set_d_plus_space(str, '+');
	if (form->space == 1 && n >= 0 && form->larg < (int)ft_strlen(str))
		str = set_d_plus_space(str, ' ');
	new = ft_strjoin(str, larg);
	return (new);
}

char		*set_moins_d_norm(t_struct *form, char *str, char *larg,
		long long n)
{
	char *new;

	if (form->moins == 0)
	{
		if (form->zero == 1)
		{
			if (form->plus == 1 && n >= 0)
				larg[0] = '+';
			if (form->space == 1 &&
					n >= 0 && form->larg > (int)ft_strlen(str))
				larg[0] = ' ';
		}
		else
		{
			if (form->plus == 1 && n >= 0)
				str = set_d_plus_space(str, '+');
			if (form->space == 1 &&
					n >= 0 && form->larg < (int)ft_strlen(str))
				str = set_d_plus_space(str, ' ');
		}
		new = ft_strjoin(larg, str);
	}
	else
		return (set_moins_d_norm_2(form, str, larg, n));
	return (new);
}

char		*set_d_0_neg(char *str, int nbr0, long long n)
{
	char	*str0;
	char	*new;
	int		i;

	(void)n;
	str0 = ft_strnew(nbr0 + 1);
	i = 1;
	str0[0] = '-';
	while (i < nbr0 + 2)
	{
		str0[i] = '0';
		i++;
	}
	str0[i] = '\0';
	new = ft_strjoin(str0, str);
	free(str0);
	return (new);
}
