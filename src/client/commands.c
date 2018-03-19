#include <ft_p.h>

static int	check_permissions_client(char *absolute_path,
	char *cur_path)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(cur_path);
		ft_printf("lcd, no permissions to access here\n");
		return (0);
	}
	return (1);
}

void		cmd_lls(char *arg)
{
	char			*open;
	DIR				*dir;
	struct dirent	*file;
	char			*name;

	if ((ft_strcmp(arg, "lls") == 0) || ft_strlen(arg) < 5)
		open = ft_strdup(".");
	else
		open = ft_strdup(&arg[4]);
	if (!(dir = opendir(open)))
	{
		ft_printf("lls, can't access to this dir\n");
		return ;
	}
	while ((file = readdir(dir)))
	{
		name = file->d_name;
		if (ft_strncmp(".", name, 1) != 0)
			ft_printf("%s\n", name);
	}
	ft_printf("\033[32mSUCCESS: lls\033[0m\n");
	closedir(dir);
}

void		cmd_lcd(char *arg, char *absolute_path)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0)
    {
		ft_printf("lcd, Failed to get arg for cd command\n");
		return;
	}
	if ((ret = chdir(dir)) == -1)
    {
		ft_printf("lcd, chdir failed\n");
		return ;
	}
	if (check_permissions_client(absolute_path, cur_path) == 0)
		return;
	ft_printf("\033[32mSUCCESS: lcd\033[0m\n");
	free(dir);
}

void		cmd_lpwd()
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
	{
		ft_printf("lpwd failed\n");
		return ;
	}
	ft_printf("%s\n", path);
	ft_printf("\033[32mSUCCESS: lpwd\033[0m\n");
}

void		cmd_lmkdir(char *arg)
{
	if (!arg || ft_strlen(arg) == 0)
	{
		ft_printf("lmkdir failed, no path specified\n");
		return ;
	}
	ft_printf("New dir: %s\n", arg);
	if (mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		ft_printf("mkdir, chdir failed\n");
	ft_printf("\033[32mSUCCESS: mkdir\033[0m\n");
}