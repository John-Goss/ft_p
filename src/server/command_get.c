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
        return ;
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
