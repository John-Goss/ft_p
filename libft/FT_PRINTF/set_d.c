/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 11:20:21 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 17:39:46 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*set_d_0(char *str, int nbr0, long long n)
{
	char	*tab[2];
	int		i;
	int		j;

	j = n < 0 ? 2 : 0;
	tab[0] = ft_strnew(nbr0 + 2);
	i = 0;
	if (str[0] == '-')
	{
		tab[0][0] = '-';
		i = 1;
	}
	while (i < nbr0 + j)
	{
		tab[0][i] = '0';
		i++;
	}
	tab[0][i] = '\0';
	if (n == -2147483648)
		str = ft_strdup("2147483648");
	else if (n < 0 && n > -2147483648)
		str = ft_itoa_base(-n, 10);
	tab[1] = ft_strjoin(tab[0], str);
	free(tab[0]);
	return (tab[1]);
}

static char		*set_d_larg(t_struct *form, char *str, long long n)
{
	char	*larg;
	int		i;

	if (form->plus == 1 && form->zero == 0)
		i = form->larg - (int)(ft_strlen(str)) - 1;
	else
		i = form->larg - (int)(ft_strlen(str));
	if (i == 0)
		return (NULL);
	if (form->zero == 1 && form->prec == -1)
	{
		if (n < 0)
		{
			larg = place(i + 1, '0');
			larg[0] = '-';
		}
		else
			larg = place(i, '0');
	}
	else
		larg = place(i, ' ');
	return (larg);
}

static char		*set_d_norm(t_struct *form, char *str, long long n)
{
	if (form->plus == 1 && n >= 0)
		str = set_d_plus_space(str, '+');
	if (form->space == 1 && n >= 0 && form->larg < (int)ft_strlen(str))
		str = set_d_plus_space(str, ' ');
	g_ret += ft_strlen(str);
	return (str);
}

static char		*set_str(t_struct *form, char *str, long long n)
{
	char	*tmp;
	char	*tmp_neg;

	tmp = ft_itoa_base(n, 10);
	tmp_neg = ft_itoa_base(-n, 10);
	if (n == 0 && form->prec == 0)
		str = ft_strdup("");
	else if (form->prec > ft_count(n))
		str = set_d_0(tmp, form->prec - ft_count(n), n);
	else if (form->prec == ft_count(n) && n < 0)
		str = set_d_0_neg(tmp_neg, form->prec - ft_count(n), -n);
	else
		str = ft_itoa_base(n, 10);
	free(tmp);
	free(tmp_neg);
	return (str);
}

char			*set_d(t_struct *form, va_list va)
{
	char		*larg;
	char		*str;
	long long	n;

	str = NULL;
	larg = NULL;
	checkflags(form, '-', '0');
	checkflags(form, '+', ' ');
	n = check_display_block_d(form, va);
	str = set_str(form, str, n);
	if (form->larg > (int)ft_strlen(str) && form->larg > form->prec)
	{
		larg = set_d_larg(form, str, n);
		str = n < 0 && form->zero == 1 ? str + 1 : str;
	}
	if (form->larg != 0 && form->larg > (int)ft_strlen(str))
		str = set_moins_d_norm(form, str, larg, n);
	else
		return (set_d_norm(form, str, n));
	g_ret += ft_strlen(str);
	free(larg);
	return (str);
}
