#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ft_p.h>

void	read_server(int fd, char *buf)
{
	int	size;

	while ((size = read(fd, buf, 1)) > 0 && buf[0] != '\0')
	{
		buf[size] = '\0';
		write(1, buf, size);
	}
}

void	local_navigation(int fd, char *buf, char *pwd)
{
	char **argv = ft_strsplit(buf, ' ');
	if (!ft_strncmp(buf, "lls", 3))
		execv("/bin/ls", argv);
	else if (!ft_strncmp(buf, "lpwd", 4))
		execv("/bin/pwd", argv);
	else if (!ft_strncmp(buf, "lmkdir", 6))
		execv("/bin/mkdir", argv);
	else if (!ft_strncmp(buf, "lcd", 3))
		cmd_lcd(buf, pwd);
	else
	{
		ft_putendl_fd(buf, fd);
		read_server(fd, buf);
	}
	free_args(argv);
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
		// else if (ft_strncmp(buf, "get ", 4) == 0 && ft_strlen(buf) > 4)
		// 	cmd_get_client(fd, &buf[3]);
		// else if (ft_strncmp(buf, "put ", 4) == 0 && ft_strlen(buf) > 4)
		// 	cmd_put_client(fd, &buf[3]);
		else
			local_navigation(fd, buf, pwd);
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