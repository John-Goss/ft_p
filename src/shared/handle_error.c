/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:53:29 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 15:51:04 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

void	handle_error(int error_type, int fd, char *message)
{
	if (!message)
		message = "unidentified";
	if (error_type == 1)
		ft_printf("Using : %s <port>\n", message);
	else if (error_type == 2)
		ft_printf("Using: %s <addr> <port>\n", message);
	else if (error_type == 3)
		ft_printf("%s\n", message);
	else if (error_type == 4)
		ft_printf("Client: %s\n", message);
	else if (error_type == 5)
		ft_printf("Server: %s\n", message);
	else if (error_type == 6)
	{
		ft_putendl_fd(message, fd);
		write(fd, "\0", 1);
		return ;
	}
	exit(-(error_type));
}

void	free_args(char **argv)
{
	char **tmp;

	tmp = argv;
	while (*tmp)
	{
		free(*tmp);
		++tmp;
	}
	free(argv);
}

int		return_error_code(char *message)
{
	ft_putstr(message);
	ft_putendl("\033[31mERROR\033[0m");
	return (0);
}

void	return_error_void(char *message)
{
	ft_putstr(message);
	ft_putendl("\033[31mERROR\033[0m");
	return ;
}
