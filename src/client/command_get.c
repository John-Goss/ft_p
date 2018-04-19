/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:31:49 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 13:49:10 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <ft_p.h>
#include <sys/socket.h>

static int		recv_get_client(int fd, int file, int size_max)
{
	char		*buff;
	int			size;
	int			n;

	n = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return (-1);
	while (n < size_max)
	{
		size = recv(fd, buff + n, 4096, 0);
		n += size;
	}
	if (write(file, buff, size_max) == -1)
		return (0);
	return (1);
}

static void		get_next(int fd)
{
	char		*line;

	if (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
}

int				cmd_get_client(int fd, char *buf)
{
	int		file;
	int		size;

	file = -1;
	if (recv_alert("RDONLY_OK", fd) < 1)
		return (return_error_code("Open() server side failed: "));
	if ((file = open_file_wronly(buf, fd)) == -1)
		return (return_error_code("Can't create the file, already exists: "));
	if (recv_alert("TEST_OK", fd) < 1)
	{
		close(file);
		return (return_error_code("Can't mapping the file: "));
	}
	if ((size = size_file(fd)) == -1)
		return (return_error_code("Can't send size from client side: "));
	(recv_get_client(fd, file, size)) == 1 ? ft_putendl_fd("SUCCESS", fd)
		: ft_putendl_fd("ERROR", fd);
	get_next(fd);
	close(file);
	return (1);
}

static int		send_put_client(struct stat st, int fd, void *ptr)
{
	char	*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	if (recv_alert("SEND", fd) < 1)
		return (1);
	send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
		return (1);
	return (0);
}

int				cmd_put_client(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf, fd)) == -1)
		return (return_error_code("Open() client side failed: "));
	if (recv_alert("WRONLY_OK", fd) < 1)
		return (return_error_code("Can't create the file, already exists: "));
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		return (return_error_code("fstat() client side failed: "));
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		close(file);
		return (return_error_code("Can't mapping the file: "));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_put_client(st, fd, ptr);
	get_next(fd);
	close(file);
	return (1);
}
