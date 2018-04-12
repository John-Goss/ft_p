#include <shared.h>
#include <ft_p.h>

static void		send_get_server(int fd, struct stat st, void *ptr, int file)
{
	char		*size;

    (void)file;
	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	if (recv_alert("SEND", fd) < 1)
	{
        ft_putstr("can't get size from client side ");
        return (display_get_status(0, fd));
    }
    send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
	{
		display_get_status(1, fd);
	}
	else
	{
		display_get_status(0, fd);
	}
}

void			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf, fd)) == -1)
	{
        ft_putstr("open() server side failed ");
        return (display_get_status(0, fd));
    }
    if (recv_alert("WRONLY_OK", fd) < 1)
    {
        ft_putstr("open() client side failed ");
		return (display_get_status(0, fd));
    }
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		ft_putstr("fstat() server side failed ");
        return (display_get_status(0, fd));
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		close(file);
		return (display_get_status(0, fd));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_get_server(fd, st, ptr, file);
	close(file);
}

static int			recv_put_server(int fd, int file, int size_max)
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

void				cmd_put_server(int fd, char *buf)
{
	int		file;
	int		size;

	file = -1;
	if (recv_alert("RDONLY_OK", fd) < 1)
		return (ft_putendl("\033[31mFAILURE\033[0m: open() client side failed"));
	if ((file = open_file_wronly(buf, fd)) == -1)
	{
		return (ft_putendl("\033[31mFAILURE\033[0m: Can't create the file already exists"));
	}
	if (recv_alert("TEST_OK", fd) < 1)
	{
		close(file);
		return (ft_putendl("\033[31mFAILURE\033[0m"));
	}
	if ((size = size_file(fd)) == -1)
		return (ft_putendl("\033[31mFAILURE\033[0m: Can't send size from server side"));
	(recv_put_server(fd, file, size) == 1) ? display_get_status(1, fd) : display_get_status(0, fd);
	close(file);	
}