/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:27:43 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 13:53:15 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (local_command_cmp(buf))
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
	char	*tab[2];

	tab[0] = malloc(sizeof(char) * UCHAR_MAX);
	getcwd(tab[0], UCHAR_MAX);
	ft_putstr("$> ");
	while ((get_next_line(0, &tab[1])) > 0)
	{
		if (ft_strcmp(tab[1], "quit") == 0)
			return ;
		else if (ft_strncmp(tab[1], "get ", 4) == 0 && ft_strlen(tab[1]) > 4)
		{
			ft_putendl_fd(tab[1], fd);
			cmd_get_client(fd, &tab[1][3]);
		}
		else if (ft_strncmp(tab[1], "put ", 4) == 0 && ft_strlen(tab[1]) > 4)
		{
			ft_putendl_fd(tab[1], fd);
			cmd_put_client(fd, &tab[1][3]);
		}
		else
			display_results(local_navigation(fd, tab[1], tab[0]), fd);
		free(tab[1]);
		ft_putstr("$> ");
	}
	free(tab[0]);
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

int		main(int ac, char **av)
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
