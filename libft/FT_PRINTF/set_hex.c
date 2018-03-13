/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 16:58:18 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 19:58:06 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*set_d_0(t_struct *form, char *str)
{
	char	*str0;
	int		nbr0;
	int		i;
	int		j;

	if (form->prec == -1 || form->prec < (int)ft_strlen(str))
		return (NULL);
	j = form->hash == 1 ? 2 : 0;
	nbr0 = form->prec - (int)ft_strlen(str);
	str0 = ft_strnew(nbr0 + 1);
	i = 0;
	while (i < (nbr0 + j))
		str0[i++] = '0';
	str0[i] = '\0';
	return (str0);
}

static char	*set_d_larg(t_struct *form, char *str)
{
	char	*larg;
	int		j;
	int		x;

	j = form->prec > (int)ft_strlen(str) ? form->prec : 0;
	x = form->hash == 1 ? 2 : 0;
	larg = NULL;
	if (form->larg == 0 || form->larg < (int)ft_strlen(str) ||
			form->larg < form->prec)
		return (NULL);
	if ((form->zero == 1 && form->prec == -1) ||
			(form->zero == 1 && form->prec < (int)ft_strlen(str)))
		larg = place(form->larg - (int)ft_strlen(str) - x, '0');
	else if (form->prec > (int)ft_strlen(str) && form->prec > form->larg)
		larg = place(j + x, ' ');
	else if (form->prec > (int)ft_strlen(str) && form->prec < form->larg)
		larg = place(form->larg - form->prec - x, ' ');
	else
		larg = place(form->larg - (int)ft_strlen(str) - x, ' ');
	return (larg);
}

static char	*set_hash(t_struct *form, char *str, char *prec, char *larg)
{
	char	*tmp;

	tmp = ft_strjoin(prec, str);
	if (form->hash == 1 && form->zero == 0)
		tmp = prec == NULL ? ft_strjoin("0x", tmp) : ft_strjoin("0x", tmp + 2);
	if (form->larg > (int)ft_strlen(tmp))
	{
		if (form->zero == 1)
		{
			if (form->hash == 1)
			{
				tmp = ft_strjoin("0x", larg);
			}
			tmp = form->hash == 0 ?
				tmp = ft_strjoin(larg, tmp) : ft_strjoin(tmp, str);
		}
		else if (form->moins == 1)
			tmp = ft_strjoin(tmp, larg);
		else
			tmp = ft_strjoin(larg, tmp);
	}
	free(str);
	free(prec);
	free(larg);
	return (tmp);
}

char		*set_hex(t_struct *form, va_list va)
{
	char		*tab[4];
	uintmax_t	n;

	tab[0] = NULL;
	tab[1] = NULL;
	tab[2] = NULL;
	tab[3] = NULL;
	checkflags(form, '-', '0');
	checkflags(form, '+', ' ');
	n = check_display_block_x(form, va);
	n == 0 && form->hash == 1 ? form->hash = 0 : 42;
	tab[0] = n == 0 && form->prec == 0 ? ft_strdup("") : u_itoa_base(n, 16);
	tab[1] = set_d_0(form, tab[0]);
	tab[2] = set_d_larg(form, tab[0]);
	tab[3] = set_hash(form, tab[0], tab[1], tab[2]);
	if (form->type == 'X')
		tab[3] = set_upper(tab[3]);
	g_ret += ft_strlen(tab[3]);
	return (tab[3]);
}
