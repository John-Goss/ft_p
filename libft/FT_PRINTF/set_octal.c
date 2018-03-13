/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_octal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:21:34 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 16:34:32 by jle-quer         ###   ########.fr       */
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
	free(str);
	free(str0);
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

static char	*set_hash(t_struct *form, uintmax_t n)
{
	char	*new;
	char	*tmp;

	tmp = NULL;
	if (n == 0 && form->prec == 0)
		new = ft_strjoin("0", NULL);
	else
	{
		tmp = u_itoa_base(n, 8);
		new = ft_strjoin("0", tmp);
		free(tmp);
	}
	return (new);
}

char		*set_octal(t_struct *form, va_list va)
{
	char		*larg;
	char		*str;
	uintmax_t	n;

	checkflags(form, '-', '0');
	checkflags(form, '+', ' ');
	n = check_display_block_o(form, va);
	if ((n == 0 && form->prec == 0) || (n == 0 && form->prec == -1))
		str = form->hash == 1 || form->prec == -1 ?
			ft_strdup("0") : ft_strdup("");
	else if (form->prec > ft_count_base(n, 8))
		str = set_d_0(u_itoa_base(n, 8), form->prec - ft_count_base(n, 8));
	else if (form->hash == 1 && form->prec < ft_count_base(n, 8))
		str = set_hash(form, n);
	else
		str = ft_itoa_base(n, 8);
	if (form->larg > (int)ft_strlen(str) && form->larg > form->prec)
	{
		larg = set_d_larg(form, str);
		str = set_moins_d(form, str, larg);
		free(larg);
	}
	g_ret += ft_strlen(str);
	return (str);
}
