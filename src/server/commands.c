/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:26:37 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 14:26:38 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

static int	check_permissions_server(char *absolute_path,
	char *cur_path, int fd)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		ft_putstr("permission denied: ");
		ft_putstr_fd("permission denied: ", fd);
		chdir(cur_path);
		return (0);
	}
	return (1);
}

int			cmd_cd(char *arg, char *absolute_path, int fd)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0 || (ret = chdir(dir)) == -1)
	{
		ft_putstr("no such file or directory: ");
		ft_putstr_fd("no such file or directory: ", fd);
		free(dir);
		return (0);
	}
	free(dir);
	return (check_permissions_server(absolute_path, cur_path, fd));
}

void		get_cmd(char **argv, int fd)
{
	if (!ft_strcmp(*argv, "ls") || !ft_strncmp(*argv, "ls ", 3))
		execv("/bin/ls", argv);
	else if (!ft_strcmp(*argv, "pwd") || !ft_strncmp(*argv, "pwd ", 4))
		execv("/bin/pwd", argv);
	else if (!ft_strncmp(*argv, "mkdir ", 6))
		execv("/bin/mkdir", argv);
	else if (!ft_strcmp(*argv, "quit"))
		exit(-1);
	else
	{
		handle_error(3, fd, "Command not found");
		exit(EXIT_FAILURE);
	}
}

void		cmd_exec_server(char *str, int fd)
{
	pid_t	pid;
	char	**argv;
	int		status;

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
