/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 12:30:53 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/14 15:19:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ui_to_bits(unsigned int u)
{
	char			*bits;
	unsigned int	i;

	bits = (char *)malloc(sizeof(char) * 33);
	if (!bits)
		return (NULL);
	ft_bzero(bits, 33);
	i = 31;
	while (u > 0)
	{
		bits[i] = (u % 2) + '0';
		u /= 2;
		i--;
	}
	return (bits);
}

static char	**uni_mask_1(char *bits, char *mask, size_t bits_len, int mask_len)
{
	char	**tmp;

	while (mask_len >= 0)
	{
		if (mask[mask_len] == 'x' && bits[bits_len])
		{
			mask[mask_len] = bits[bits_len];
			bits_len--;
		}
		else if (mask[mask_len] == 'x' && !bits[bits_len])
			mask[mask_len] = '0';
		mask_len--;
	}
	tmp = ft_strsplit(mask, ' ');
	return (tmp);
}

static char	**uni_mask(char *bits)
{
	char	*mask;
	size_t	bits_len;
	int		mask_len;

	mask = NULL;
	bits_len = 31;
	while (bits[bits_len])
		bits_len--;
	bits_len = 31 - bits_len;
	if (bits_len <= 7)
		mask = ft_strdup("0xxxxxxx ");
	else if (bits_len > 7 && bits_len <= 11)
		mask = ft_strdup("110xxxxx 10xxxxxx");
	else if (bits_len > 11 && bits_len <= 16)
		mask = ft_strdup("1110xxxx 10xxxxxx 10xxxxxx");
	else if (bits_len > 16)
		mask = ft_strdup("11110xxx 10xxxxxx 10xxxxxx 10xxxxxx");
	mask_len = ft_strlen(mask) - 1;
	bits_len = 31;
	return (uni_mask_1(bits, mask, bits_len, mask_len));
}

static void	print_oct(char *mask)
{
	int	power;
	int	value;
	int	i;

	i = 0;
	value = 0;
	power = 7;
	while (i < 8)
	{
		if (mask[i] == '0')
			power--;
		else
		{
			value += ft_power(2, power);
			power--;
		}
		i++;
	}
	ft_putint(value);
}

void		ft_putwchar(wchar_t c)
{
	char	*bits;
	char	**mask;
	int		i;

	bits = ui_to_bits((unsigned int)c);
	mask = uni_mask(bits);
	i = 0;
	while (mask && mask[i])
	{
		print_oct(mask[i]);
		free(mask[i]);
		i++;
	}
	free(bits);
	free(mask);
}
