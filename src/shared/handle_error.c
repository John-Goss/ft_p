#include <shared.h>

void    handle_error(int error_type, char *message)
{
    if (!message)
        message = "unidentified";
    if (error_type == 1)
        ft_printf("Using : %s <port>\n", message);
    else if (error_type == 2)
		ft_printf("Using: %s <addr> <port>\n", message);
    else if (error_type == 3)
		ft_printf("Error: %s\n", message);
    else if (error_type == 4)
        ft_printf("Client: %s\n", message);
    else if (error_type == 5)
        ft_printf("Server: %s\n", message);
    exit (-(error_type));
}