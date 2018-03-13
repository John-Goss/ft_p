/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 15:50:13 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 17:06:24 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_format(const char *format)
{
	t_struct	form;
	int			i;

	i = 0;
	init_struct(&form);
	while ((check_options(format[i], &form)) == 1)
		i++;
	while ((check_minimal_large(format[i], &form)) == 1)
		i++;
	if (format[i] == '.')
	{
		form.prec = 0;
		while ((check_precision(format[++i], &form)) == 1)
			continue;
	}
	while (format[i] == 'h' || format[i] == 'l' || format[i] == 'j'
			|| format[i] == 'z')
	{
		check_size_modifier(format + i, &form);
		i++;
		if ((&form)->hh > 0 || (&form)->ll > 0)
			i++;
	}
	check_type(format[i]) == 1 ? (&form)->type = format[i] : 0;
	return (check_block(ft_strsub(format, 0, i + 1), &form));
}

int		check_options(const char format, t_struct *form)
{
	if (format != '-' && format != '+' && format != '#' && format != '0'
			&& format != ' ')
		return (0);
	else if (format == '-')
		form->moins = 1;
	else if (format == '+')
		form->plus = 1;
	else if (format == '#')
		form->hash = 1;
	else if (format == '0')
		form->zero = 1;
	else if (format == ' ')
		form->space = 1;
	return (1);
}

int		check_minimal_large(const char format, t_struct *form)
{
	if ((format - 48) >= 0 && (format - 48) <= 9)
	{
		form->larg = form->larg * 10 + (format - 48);
		return (1);
	}
	else
		return (0);
}

int		check_precision(const char format, t_struct *form)
{
	if ((format - 48) >= 0 && (format - 48) <= 9)
	{
		form->prec = form->prec * 10 + (format - 48);
		return (1);
	}
	else
		return (0);
}

void	check_size_modifier(const char *format, t_struct *form)
{
	if (format[0] == 'h' && format[1] != 'h')
		form->h = 1;
	else if (format[0] == 'h' && format[1] == 'h')
		form->hh = 1;
	else if (format[0] == 'l' && format[1] != 'l')
		form->l = 1;
	else if (format[0] == 'l' && format[1] == 'l')
		form->ll = 1;
	else if (format[0] == 'j')
		form->j = 1;
	else if (format[0] == 'z')
		form->z = 1;
}
