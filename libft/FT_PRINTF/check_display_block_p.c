/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_display_block_p.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 04:28:33 by jle-quer          #+#    #+#             */
/*   Updated: 2016/02/27 04:54:22 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long	check_display_block_p(va_list va)
{
	unsigned long	p;

	p = (unsigned long)va_arg(va, void *);
	return (p);
}
