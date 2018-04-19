/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:27:18 by jle-quer          #+#    #+#             */
/*   Updated: 2018/04/18 14:59:25 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

void	handle_error(int error_type, int fd, char *message);
int		return_error_code(char *message);
void	return_error_void(char *message);
void	free_args(char **argv);
int		recv_alert(char *str, int fd);
int		size_file(int fd);
int		open_file_wronly(char *cmd, int fd);
int		open_file_rdonly(char *cmd, int client);

#endif
