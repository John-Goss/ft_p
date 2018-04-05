#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ft_p.h>

void	read_server(int fd, char *buf)
{
	int	size;

	size = 0;
	while ((size = read(fd, buf, 1)) > 0 && buf[0] != '\0')
	{
		buf[size] = '\0';
		write(1, buf, size);
	}
}

int		local_navigation(int fd, char *buf, char *pwd)
{
	char	**argv;
	int		ret;

	ret = 0;
	argv = ft_strsplit(buf, ' ');
	if (!ft_strcmp(buf, ""))
		ret = 2;
	else if (!ft_strncmp(buf, "lcd ", 4))
	{
		display_server_local_cmd(buf, fd);
		ret = cmd_lcd(buf + 4, pwd);
	}
	else if (!ft_strcmp(buf, "lls") || !ft_strncmp(buf, "lls ", 4)
	|| !ft_strcmp(buf, "lpwd") || !ft_strncmp(buf, "lpwd ", 5)
	|| !ft_strncmp(buf, "lmkdir ", 7))
	{
		display_server_local_cmd(buf, fd);
		ret = cmd_exec_client(argv);
	}
	else
	{
		ret = 2;
		ft_putendl_fd(buf, fd);
		read_server(fd, buf);
	}
	free_args(argv);
	return (ret);
}

void	user_cmd(int fd)
{
	int		r;
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = malloc(sizeof(char) * UCHAR_MAX);
	getcwd(pwd, UCHAR_MAX);
	ft_putstr("$> ");
	while ((r = get_next_line(0, &buf)) > 0)
	{
		if (ft_strcmp(buf, "quit") == 0)
			return ;
		else if (ft_strncmp(buf, "get ", 4) == 0 && ft_strlen(buf) > 4)
		{
			ft_putendl_fd(buf, fd);
			cmd_get_client(fd, &buf[3]);
		}
		// else if (ft_strncmp(buf, "put ", 4) == 0 && ft_strlen(buf) > 4)
		// 	cmd_put_client(fd, &buf[3]);
		else
			display_results(local_navigation(fd, buf, pwd), fd);
		free(buf);
		ft_putstr("$> ");
	}
	free(pwd);
}

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		handle_error(4, 0, "connection error");
	return (sock);
}

int		main (int ac, char **av)
{
	int port;
	int	socket;

	if (ac != 3)
		handle_error(2, 0, av[0]);
	port = atoi(av[2]);
	if ((socket = create_client(av[1], port)) < 0)
		handle_error(3, 0, "socket not found");
	user_cmd(socket);
	close(socket);
	return (0);
}