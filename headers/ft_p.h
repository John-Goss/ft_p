/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:27:05 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 14:59:01 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H
# include <libft.h>
# include <shared.h>
# include <get_next_line.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>

/*
** Server
*/

int		cmd_cd(char *arg, char *absolute_path, int fd);
void	cmd_exec_server(char *str, int fd);
void	display_status(int status, int fd);
void	display_get_status(int status, int fd);
void	display_success_failure(int val, int fd);
void	cmd_get_server(int fd, char *buf);
void	cmd_put_server(int fd, char *buf);

/*
** Client
*/

int		cmd_exec_client(char **argv);
int		cmd_lcd(char *arg, char *absolute_path);
void	display_results(int status, int fd);
void	display_server_local_cmd(char *cmd, int fd);
int		display_local_status(int status);
int		cmd_get_client(int fd, char *buf);
int		cmd_put_client(int fd, char *buf);
int		local_command_cmp(char *cmd);

#endif
