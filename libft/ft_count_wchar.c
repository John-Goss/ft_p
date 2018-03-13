/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_wchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 14:37:46 by jle-quer          #+#    #+#             */
/*   Updated: 2016/02/19 15:32:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_wchar(unsigned int wchar)
{
	if (wchar < 128)
		return (1);
	else if (wchar < 2048)
		return (2);
	else if (wchar < 65536)
		return (3);
	else
		return (4);
}
