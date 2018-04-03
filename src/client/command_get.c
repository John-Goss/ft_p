#include <ft_p.h>
#include <shared.h>

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
	write(file, buff, size_max);
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

int 			cmd_get_client(int fd, char *buf)
{
	int			file;
	int			size;

	file = -1;
	if (recv_alert("RDONLY_OK", fd) < 1)
	{
        ft_putendl("ERROR: open() server side failed");
    	return (0);
    }
    if ((file = open_file_wronly(buf + 4, fd)) == -1)
	{
        ft_putendl("ERROR: Can't create the file, already exists");
		return (0);
	}
	if (recv_alert("WRONLY_OK", fd) < 1)
	{
		close(file);
		return (0);
	}
	if ((size = size_file(fd)) == -1)
	{
        ft_putendl("ERROR: Can't send size from client side");
       	return (0);
    }
    recv_get_client(fd, file, size);
	get_next(fd);
	close(file);
    return (1);
}