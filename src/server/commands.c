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
