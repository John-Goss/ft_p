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