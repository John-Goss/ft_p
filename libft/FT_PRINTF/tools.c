/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:09:07 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 15:58:02 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	checkflags(t_struct *strct, char a, char b)
{
	if (a == '-' && b == '0')
	{
		if (strct->moins == 1 && strct->zero == 1)
			strct->zero = 0;
	}
	if (a == '+' && b == ' ')
	{
		if (strct->space == 1 && strct->plus == 1)
			strct->space = 0;
	}
}

char	*place(int n, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strnew(n + 1);
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*place_s(int n, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strnew(n + 1);
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*set_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

char	*set_d_plus_space(char *str, char c)
{
	char	*new;

	new = ft_strnew(1);
	new[0] = c;
	str = ft_strjoin(new, str);
	free(new);
	return (str);
}
