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
/*
void		cmd_ls(int fd, char *arg)
{
	// char			*open;
	// DIR				*dir;
	// struct dirent	*file;
	// char			*name;

	// if ((ft_strcmp(arg, "ls") == 0) || ft_strlen(arg) < 4)
	// 	open = ft_strdup(".");
	// else
	// 	open = ft_strdup(&arg[3]);
	// if (!(dir = opendir(open)))
	// {
	// 	return (handle_error(6, fd, "ls, can't access to this dir"));
	// }
	// while ((file = readdir(dir)))
	// {
	// 	name = file->d_name;
	// 	if (ft_strncmp(".", name, 1) != 0)
	// 		ft_putendl_fd(name, fd);
	// }
	// ft_putendl_fd("\033[32mSUCCESS: ls\033[0m", fd);
    // write(fd, "\0", 1);
	// closedir(dir);
	(void)arg;
	char *argv[]={"./", "-la", NULL};
	if (fork() == 0)
	{
		dup2(fd, 1);
		execv("/bin/ls", argv);
		write(fd, "\0", 1);
	}
}
*/
int			cmd_cd(char *arg, char *absolute_path)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0)
        return (0);
    if ((ret = chdir(dir)) == -1)
        return (0);
    ret = check_permissions_server(absolute_path, cur_path);
	free(dir);
	if (ret == 1)
		return (1);
	return (0);
}
/*
void		cmd_pwd(int fd)
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
		return (handle_error(6, fd, "pwd failed"));
    ft_putendl_fd(path, fd);
	ft_putendl_fd("\033[32mSUCCESS: pwd\033[0m", fd);
    write(fd, "\0", 1);
}

void		cmd_mkdir(int fd, char *arg)
{
	if (!arg || ft_strlen(arg) == 0)
		return (handle_error(6, fd, "mkdir failed, no path specified"));
	ft_printf("New dir: %s\n", arg);
	if (mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		handle_error(6, fd, "mkdir, chdir failed");
	ft_putendl_fd("\033[32mSUCCESS: mkdir\033[0m", fd);
    write(fd, "\0", 1);
}
*/

