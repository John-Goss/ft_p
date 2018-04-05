#include <ft_p.h>

void	display_status(int status, int fd)
{
	if (WEXITSTATUS(status) == 0)
	{
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
		ft_putendl("\033[32mSUCCESS\033[0m");
	}
	else
	{
		ft_putendl_fd("\033[31mFAILURE\033[0m", fd);
		ft_putendl("\033[31mFAILURE\033[0m");
	}
	write(fd, "\0", 1);
}

void	display_get_status(int status, int fd)
{
	if (status == 1)
	{
		ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
		ft_putendl("\033[32mSUCCESS\033[0m");
	}
	else
	{
		ft_putendl_fd("\033[31mFAILURE\033[0m", fd);
		ft_putendl("\033[31mFAILURE\033[0m");
	}
	write(fd, "\0", 1);
}