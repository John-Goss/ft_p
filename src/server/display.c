/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:26:43 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 14:26:44 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

void	display_status(int status, int fd)
{
	if (WEXITSTATUS(status) == 0)
	{
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
		ft_putendl("\033[32mSUCCESS\033[0m");
	}
	else
	{
		ft_putendl_fd("\033[31mERROR\033[0m", fd);
		ft_putendl("\033[31mERROR\033[0m");
	}
	write(fd, "\0", 1);
}

void	display_get_status(int status, int fd)
{
	if (status == 1)
	{
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
		ft_putendl("\033[32mSUCCESS\033[0m");
		write(fd, "\0", 1);
	}
	else
	{
		ft_putendl("\033[31mERROR\033[0m");
	}
}

void	display_success_failure(int val, int fd)
{
	if (val)
	{
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
		ft_putendl("\033[32mSUCCESS\033[0m");
	}
	else
	{
		ft_putendl_fd("\033[31mERROR\033[0m", fd);
		ft_putendl("\033[31mERROR\033[0m");
	}
}
