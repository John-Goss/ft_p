#include <ft_p.h>

void	display_server_local_cmd(char *cmd, int fd)
{
	ft_putstr_fd("Local [", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd("]: ", fd);
}

void	display_results(int status, int fd)
{
	if (status == 0)
	{
		ft_putendl_fd("\033[31mFAILURE\033[0m", fd);
	}
	else if (status == 1)
	{
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
	}
	write (fd, "\0", 1);
}

int		display_local_status(int status)
{
	if (WEXITSTATUS(status) == 0)
	{
		ft_putendl("\033[32mSUCCESS\033[0m");
		return (1);
	}
	else
	{
		ft_putendl("\033[31mFAILURE\033[0m");
		return (0);
	}
}