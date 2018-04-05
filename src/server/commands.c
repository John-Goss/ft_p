#include <ft_p.h>

static int	check_permissions_server(char *absolute_path,
	char *cur_path)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(cur_path);
		return (0);
	}
	return (1);
}

int			cmd_cd(char *arg, char *absolute_path)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0 || (ret = chdir(dir)) == -1)
	{
		free(dir);
        return (0);
	}
	free(dir);
	return (check_permissions_server(absolute_path, cur_path));
}

void	get_cmd(char **argv, int fd)
{
	if (!ft_strcmp(*argv, "ls") || !ft_strncmp(*argv, "ls ", 3))
		execv("/bin/ls", argv);
	else if (!ft_strcmp(*argv, "pwd") || !ft_strncmp(*argv, "pwd ", 4))
		execv("/bin/pwd", argv);
	else if (!ft_strncmp(*argv, "mkdir ", 6))
		execv("/bin/mkdir", argv);
	else if (!ft_strcmp(*argv, "quit"))
		exit (-1);
	else
	{
		handle_error(3, fd, "Command not found");
		exit(EXIT_FAILURE);
	}
}

void		cmd_exec_server(char *str, int fd)
{
	int 	status;
	pid_t	pid;
	char	**argv;
	
	argv = ft_strsplit(str, ' ');
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
		ft_putendl_fd("\033[31mFAILURE: FORK ERROR\033[0m", fd);
	free_args(argv);
}