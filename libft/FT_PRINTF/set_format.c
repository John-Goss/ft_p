/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:01:00 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 16:00:08 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_format(const char *format, va_list va)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar(format[i]);
			g_ret += 1;
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar(format[i]);
			g_ret += 1;
			i++;
		}
		else if (format[i] == '%' && format[i + 1] != '%'
				&& format[i + 1] != '\0')
			i += set_block(format + i + 1, va) + 1;
		i++;
	}
}

int		set_block(const char *format, va_list va)
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
	return (display_block(&form, va, i));
}
