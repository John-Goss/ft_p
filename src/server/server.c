#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ft_p.h>

int		get_cmd(char *str, int fd, char *pwd)
{
	ft_printf("$> %s\n", str);
	if (ft_strncmp(str, "ls", 2) == 0 && ft_strlen(str) >= 2)
		cmd_ls(fd, str);
	else if (ft_strncmp(str, "cd ", 3) == 0 && ft_strlen(str) > 3)
		cmd_cd(fd, &str[3], pwd);
	// else if (ft_strncmp(str, "get ", 4) == 0 && ft_strlen(str) > 4)
	// 	cmd_get_server(fd, &str[4]);
	// else if (ft_strncmp(str, "put ", 4) == 0 && ft_strlen(str) > 4)
	// 	cmd_put_server(fd, &str[4]);
	else if (ft_strcmp(str, "quit") == 0 && ft_strlen(str) == 4)
		return (-1);
	else if (ft_strcmp(str, "pwd") == 0 && ft_strlen(str) == 3)
		cmd_pwd(fd);
	else if (ft_strncmp(str, "mkdir ", 6) == 0 && ft_strlen(str) > 6)
		cmd_mkdir(fd, &str[6]);
	else if ((ft_strncmp(str, "lls", 3) == 0 && ft_strlen(str) >= 3) ||
	(ft_strncmp(str, "lcd ", 4) == 0 && ft_strlen(str) > 4) ||
	(ft_strcmp(str, "lpwd") == 0 && ft_strlen(str) == 4) ||
	(ft_strncmp(str, "lmkdir ", 7) == 0 && ft_strlen(str) > 7))
		ft_printf("\033[32mSUCCESS: local client\033[0m\n");
	else
		handle_error(6, fd, "Command not found");
	return (1);
}


void	handle_server(int socket)
{
	char	*pwd;
	char	*buf;

	pwd = malloc(sizeof(char) * UCHAR_MAX);
	getcwd(pwd, UCHAR_MAX);
	while (42)
	{
		if (get_next_line(socket, &buf) > 0)
		{
			if (get_cmd(buf, socket, pwd) == -1)
				break;
		}
		else
			break;
		free(buf);
	}
	free(pwd);
	close(socket);
}

int		handle_fork(int socket)
{
	pid_t				pid;
	int					client_socket;

	ft_printf("Waiting for a client!\n");
	while (42)
	{
		if ((client_socket = accept(socket, (struct sockaddr*)NULL, NULL)))
		{
			if ((pid = fork()) == -1)
				return (-1);
			else if (pid == 0)
			{
				ft_printf("\nNew client!\n");
				handle_server(client_socket);
				ft_printf("\nClient disconnect\n");
				break ;
			}
		}
		else
			handle_error(5, 0, "accept failed");
	}
	close(client_socket);
	return (0);
}

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	ft_memset((void *)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		handle_error(5, 0, "bind error");
	if (listen(sock, 42) == -1)
		handle_error(5, 0, "listen error");
	return (sock);
}

int		main (int ac, char **av)
{
	int	port;
	int	socket;

	if (ac != 2)
		handle_error(1, 0, av[0]);
	port = atoi(av[1]);
	if ((socket = create_server(port)) < 0)
		handle_error(3, 0, "protocol not recognized");
	if ((handle_fork(socket)) == -1)
		handle_error(5, 0, "fork failed");
	close(socket);
	return (0);
}