#include <shared.h>

int		recv_alert(char *str, int fd)
{
	char	*buf;

	buf = NULL;
	if (get_next_line(fd, &buf) > 0)
	{
		if (ft_strcmp(buf, str) == 0)
			return (1);
	}
	return (-1);
}

int		size_file(int fd)
{
	int			size;
	char		*line;

	size = 0;
	line = NULL;
	if (get_next_line(fd, &line) == 1)
	{
		size = ft_atoi(line);
		if (size < 1)
		{
			ft_putendl(line);
			ft_putendl_fd("ERROR_FILESIZE", fd);
			free(line);
			return (-1);
		}
		free(line);
	}
	else
		return (-1);
	ft_putendl_fd("SEND", fd);
	return (size);
}

int		open_file_wronly(char *cmd, int fd)
{
	char		*filename;
	int			file;

	filename = cmd;
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
		S_IRWXU | S_IRGRP | S_IROTH)) == -1)
		ft_putendl_fd("ERROR_WRONLY", fd);
	else
		ft_putendl_fd("WRONLY_OK", fd);
	return (file);
}

int		open_file_rdonly(char *cmd, int client)
{
	char		*filename;
	int			file;

	filename = cmd;
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
		ft_putendl_fd("ERROR_RONDLY", client);
	else
		ft_putendl_fd("RDONLY_OK", client);
	return (file);
}