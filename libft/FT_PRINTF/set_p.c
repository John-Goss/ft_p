/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 04:27:39 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 19:07:29 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*set_d_0(char *str, int nbr0)
{
	char	*str0;
	char	*new;
	int		i;

	str0 = ft_strnew(nbr0 + 1);
	i = 0;
	while (i < nbr0)
	{
		str0[i] = '0';
		i++;
	}
	str0[i] = '\0';
	new = ft_strjoin(str0, str);
	free(str0);
	free(str);
	return (new);
}

static char	*set_d_larg(t_struct *form, char *str)
{
	char *larg;

	if (form->zero == 1 && form->prec == -1)
		larg = place(form->larg - ft_strlen(str), '0');
	else
		larg = place(form->larg - ft_strlen(str), ' ');
	return (larg);
}

static char	*set_moins_d(t_struct *form, char *str, char *larg)
{
	char	*new;

	if (form->moins == 0)
		new = ft_strjoin(larg, str);
	else
		new = ft_strjoin(str, larg);
	return (new);
}

char		*set_p(t_struct *form, va_list va)
{
	char			*tab[3];
	unsigned long	n;

	checkflags(form, '-', '0');
	checkflags(form, '+', ' ');
	n = check_display_block_p(va);
	if (n == 0 && form->prec == 0)
		tab[0] = ft_strdup("0x");
	else if (form->prec > ft_count_base(n, 16))
	{
		tab[1] = set_d_0(ft_itoa_base(n, 16),
				form->prec - ft_count_base(n, 16));
		tab[0] = ft_strjoin("0x", tab[1]);
		free(tab[1]);
	}
	else
		tab[0] = ft_strjoin("0x", ft_itoa_base(n, 16));
	if (form->larg > (int)ft_strlen(tab[0]) && form->larg > form->prec)
	{
		tab[2] = set_d_larg(form, tab[0]);
		tab[0] = set_moins_d(form, tab[0], tab[2]);
		free(tab[2]);
	}
	g_ret += ft_strlen(tab[0]);
	return (tab[0]);
}
