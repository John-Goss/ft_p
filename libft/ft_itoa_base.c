/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 05:25:19 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/14 14:46:36 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*u_itoa_base(uintmax_t nbr, int base)
{
	char			*ret;
	int				size;

	ret = NULL;
	size = ft_count_base(nbr, base);
	if ((ret = (char *)malloc(sizeof(char) * size + 1)))
	{
		ret[size--] = '\0';
		while (size >= 0)
		{
			if (base > 10)
			{
				ret[size] = (nbr % base) >= 10 ?
				(nbr % base) - 10 + 'a' : (nbr % base) + '0';
			}
			else
				ret[size] = (nbr % base) + '0';
			nbr /= base;
			size--;
		}
	}
	return (ret);
}

char	*ft_itoa_base(intmax_t nbr, int base)
{
	char			*ret;
	int				size;
	int				is_neg;

	if (base != 10)
		return (u_itoa_base((uintmax_t)nbr, base));
	if (nbr == (-9223372036854775807 - 1))
		return (ft_strdup("-9223372036854775808"));
	ret = NULL;
	size = nbr < 0 ? 1 : 0;
	is_neg = nbr < 0 ? 1 : 0;
	nbr = nbr < 0 ? -nbr : nbr;
	size += ft_count(nbr);
	if ((ret = (char *)malloc(sizeof(char) * size + 1)))
	{
		ret[size--] = '\0';
		while (nbr >= 0 && size >= 0)
		{
			ret[size--] = (nbr % base) + '0';
			nbr /= base;
		}
		if (is_neg == 1)
			ret[++size] = '-';
	}
	return (ret);
}
