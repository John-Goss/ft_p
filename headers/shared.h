#ifndef SHARED_H
# define SHARED_H

#include <libft.h>
#include <ft_p.h>

void    handle_error(int error_type, int fd, char *message);
void    free_args(char **argv);
int     recv_alert(char *str, int fd);
int     size_file(int fd);
int     open_file_wronly(char *cmd, int fd);
int     open_file_rdonly(char *cmd, int client);

#endif
