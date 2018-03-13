#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libft.h>
#include <shared.h>

int	create_client(char *addr, int port)
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
		handle_error(4, "connection error");
	return (sock);
}

int	main (int ac, char **av)
{
	int port;
	int	socket;

	if (ac != 3)
		handle_error(2, av[0]);
	port = atoi(av[2]);
	if ((socket = create_client(av[1], port)) < 0)
		handle_error(3, NULL);
	write(socket, "Hello World!\n", 13);
	close(socket);
	return (0);
}