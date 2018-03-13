/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 22:41:43 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/10 19:15:47 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	set_c_gret(t_struct *form, char *larg, wchar_t c)
{
	if (form->type == 'C' || form->l == 1)
		g_ret += ft_count_wchar(c);
	else
		g_ret += 1;
	g_ret += larg != NULL ? ft_strlen(larg) : 0;
}

void			set_c(t_struct *f, va_list va)
{
	wchar_t		c;
	char		*larg;
	int			y;

	larg = NULL;
	c = f->type == 'C' || f->l == 1 ? va_arg(va, wchar_t) : va_arg(va, int);
	y = f->type == 'C' || f->l == 1 ? ft_count_wchar(c) : 1;
	if (f->larg > 0)
	{
		larg = place(f->larg - y, ' ');
		if (f->moins == 1)
		{
			f->type == 'C' || f->l == 1 ? ft_putwchar(c) : ft_putchar(c);
			ft_putstr(larg);
		}
		else
		{
			ft_putstr(larg);
			f->type == 'C' || f->l == 1 ? ft_putwchar(c) : ft_putchar(c);
		}
	}
	else
		f->type == 'C' || f->l == 1 ? ft_putwchar(c) : ft_putchar(c);
	set_c_gret(f, larg, c);
	free(larg);
}
