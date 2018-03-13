#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libft.h>
#include <shared.h>

int	create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		handle_error(5, "bind error");
	listen(sock, 42);
	return (sock);
}

int	main (int ac, char **av)
{
	int 				port;
	int					socket;
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	int					read_size;
	char				buf[1024];

	if (ac != 2)
		handle_error(1, av[0]);
	port = atoi(av[1]);
	if ((socket = create_server(port)) < 0)
		handle_error(3, "protocol not recognized");
	cs = accept(socket, (struct sockaddr*)&csin, &cslen);
	while ((read_size = read(cs, buf, 1023)) > 0)
	{
		buf[read_size] = '\0';
		ft_printf("received %d bytes: [%s]\n", read_size, buf);
	}
	close(cs);
	close(socket);
	return (0);
}