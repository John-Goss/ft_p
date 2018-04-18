/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:26:31 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 14:26:33 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <ft_p.h>

static void		puts_get_error(char *message, int fd)
{
	ft_putstr(message);
	return (display_get_status(0, fd));
}

static void		send_get_server(int fd, struct stat st, void *ptr)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	if (recv_alert("SEND", fd) < 1)
		return (puts_get_error("Can't get size from client side: ", fd));
	send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
		display_get_status(1, fd);
	else
		display_get_status(0, fd);
}

void			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf, fd)) == -1)
		return (puts_get_error("Open() server side failed: ", fd));
	if (recv_alert("WRONLY_OK", fd) < 1)
		return (puts_get_error("Open() client side failed: ", fd));
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		return (puts_get_error("fstat() server side failed: ", fd));
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		close(file);
		return (puts_get_error("Can't mapping the file: ", fd));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_get_server(fd, st, ptr);
	close(file);
}

static int		recv_put_server(int fd, int file, int size_max)
{
	char			*buff;
	int				size;
	int				n;

	n = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return (-1);
	while (n < size_max)
	{
		size = recv(fd, buff + n, 4096, 0);
		if (size % 4096 != 0)
			break ;
		n += size;
	}
	if (write(file, buff, size_max) == -1)
	{
		ft_putendl_fd("ERROR", fd);
		return (0);
	}
	ft_putendl_fd("SUCCESS", fd);
	return (1);
}

void			cmd_put_server(int fd, char *buf)
{
	int		file;
	int		size;

	file = -1;
	if (recv_alert("RDONLY_OK", fd) < 1)
		return (return_error_void("Open() client side failed: "));
	if ((file = open_file_wronly(buf, fd)) == -1)
		return (return_error_void("Can't create the file already exists: "));
	if (recv_alert("TEST_OK", fd) < 1)
	{
		close(file);
		return (ft_putendl("\033[31mERROR\033[0m"));
	}
	if ((size = size_file(fd)) == -1)
		return (return_error_void("Can't send size from server side: "));
	(recv_put_server(fd, file, size) == 1) ? display_get_status(1, fd)
	: display_get_status(0, fd);
	close(file);
}
