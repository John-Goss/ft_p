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
        ft_putendl("can't get size from client side");
        return ;
    }
    send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
		ft_putendl_fd("\033[32mSUCCESS: get\033[0m", fd);
}

void			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf + 4, fd)) == -1)
	{
        ft_putendl("open() server side failed");
        return ;
    }
    if (recv_alert("WRONLY_OK", fd) < 1)
    {
        ft_putendl("open() client side failed");
		return ;
    }
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		ft_putendl("fstat() server side failed");
        return ;
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		close(file);
		return (ft_putendl("\033[32mSUCCESS: get\033[0m"));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_get_server(fd, st, ptr, file);
	close(file);
}
