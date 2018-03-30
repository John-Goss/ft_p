#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ft_p.h>

void	get_cmd(char **argv, int fd)
{
	if (!ft_strncmp(*argv, "ls", 2))
		execv("/bin/ls", argv);
	else if (!ft_strncmp(*argv, "pwd", 3))
		execv("/bin/pwd", argv);
	else if (!ft_strncmp(*argv, "mkdir", 5))
		execv("/bin/mkdir", argv);
	else if (!ft_strcmp(*argv, "quit"))
		exit (-1);
	else
	{
		handle_error(3, fd, "Command not found");
		exit(EXIT_FAILURE);
	}
}

void	display_status(int status, int fd)
{
	if (WEXITSTATUS(status) == 0)
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
    else
		ft_putendl_fd("\033[31mFAILLURE\033[0m", fd);
	write(fd, "\0", 1);
}

int		handle_command(char *str, int fd, char *pwd)
{
	int 	status;
	pid_t	pid;
	
	char **argv = ft_strsplit(str, ' ');
	ft_printf("$> %s\n", str);
	if (!ft_strncmp(str, "cd", 2))
	{
		if (cmd_cd(&str[3], pwd) == 1)
			ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
		else
			ft_putendl_fd("\033[31mFAILLURE\033[0m", fd);
		write(fd, "\0", 1);
	}
	else
	{
		pid = fork();
		if (pid > 0)
		{
			wait4(pid, &status, 0, NULL);
			display_status(status, fd);
		}
		else if (pid == 0)
		{
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			close(fd);
			get_cmd(argv, fd);
		}
		else
		{
			free_args(argv);
			ft_putendl_fd("\033[31mFAILLURE: FORK ERROR\033[0m", fd);
			return (0);
		}
	}
	free_args(argv);
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
			if (handle_command(buf, socket, pwd) == -1)
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