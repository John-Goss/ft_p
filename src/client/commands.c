/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:08:04 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 14:08:06 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

static int	cd_check_permissions_client(char *absolute_path,
	char *cur_path)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(cur_path);
		ft_putendl("permission denied: \033[31mERROR\033[0m");
		return (0);
	}
	return (1);
}

int			cmd_lcd(char *arg, char *absolute_path)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0)
	{
		ft_putendl("failed to get arg for cd command: \033[31mERROR\033[0m");
		return (0);
	}
	if ((ret = chdir(dir)) == -1)
	{
		ft_putendl("chdir failed: \033[31mERROR\033[0m");
		return (0);
	}
	if (cd_check_permissions_client(absolute_path, cur_path) == 0)
		return (0);
	ft_putendl("\033[32mSUCCESS\033[0m");
	free(dir);
	return (1);
}

int			cmd_exec_client(char **argv)
{
	pid_t	pid;
	int		status;

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
		else if (!ft_strcmp(*argv, "lpwd"))
			execv("/bin/pwd", argv);
		else if (!ft_strcmp(*argv, "lmkdir"))
			execv("/bin/mkdir", argv);
	}
	else
		ft_putendl("\033[31mLOCAL ERROR: fork failed\033[0m");
	return (0);
}

int			local_command_cmp(char *cmd)
{
	if (!ft_strcmp(cmd, "lls") || !ft_strncmp(cmd, "lls ", 4)
	|| !ft_strcmp(cmd, "lpwd") || !ft_strncmp(cmd, "lpwd ", 5)
	|| !ft_strcmp(cmd, "lmkdir") || !ft_strncmp(cmd, "lmkdir ", 7))
		return (1);
	return (0);
}
