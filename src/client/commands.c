#include <ft_p.h>

static int	cd_check_permissions_client(char *absolute_path,
	char *cur_path)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(cur_path);
		ft_putendl("\033[31mFAILURE: lcd, no permissions to access here\033[0m");
		return (0);
	}
	return (1);
}

int		cmd_lcd(char *arg, char *absolute_path)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0)
    {
		ft_putendl("\033[31mFAILURE: lcd, Failed to get arg for cd command\033[0m");
		return (0);
	}
	if ((ret = chdir(dir)) == -1)
    {
		ft_putendl("\033[31mFAILURE: lcd, chdir failed\033[0m");
		return (0);
	}
	if (cd_check_permissions_client(absolute_path, cur_path) == 0)
		return (0);
	ft_putendl("\033[32mSUCCESS: lcd\033[0m");
	free(dir);
	return (1);
}

int		cmd_exec_client(char **argv)
{
	int 	status;
	pid_t	pid;
	
	pid = fork();
	if (pid > 0)
	{
		wait4(pid, &status, 0, NULL);
		return (display_local_status(status));
	}
	else if (pid == 0)
	{
		if (!ft_strncmp(*argv, "lls", 3))
			execv("/bin/ls", argv);
		else if (!ft_strncmp(*argv, "lpwd", 4))
			execv("/bin/pwd", argv);
		else if (!ft_strncmp(*argv, "lmkdir", 6))
			execv("/bin/mkdir", argv);
	}
	else
		ft_putendl("\033[31mLOCAL FAILURE: FORK ERROR\033[0m");
	return (0);
}