/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:33:06 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/14 14:42:53 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_struct	*get_new_struct(int const fd, t_struct *next)
{
	t_struct	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	if (next == NULL)
		new->next = new;
	else
		new->next = next;
	new->fd = fd;
	ft_bzero(new->buf, BUFF_SIZE + 1);
	new->save_buf = NULL;
	return (new);
}

static void		get_create_line(int const fd, t_struct **struc)
{
	t_struct	*new;

	new = *struc;
	if (*struc == NULL)
	{
		*struc = get_new_struct(fd, NULL);
		return ;
	}
	while (new->next != *struc && new->fd != fd)
		new = new->next;
	if (new->fd != fd)
	{
		new->next = get_new_struct(fd, new->next);
		*struc = new->next;
		return ;
	}
	*struc = new;
	ft_bzero((*struc)->buf, BUFF_SIZE + 1);
}

static int		get_return_line(char **line, t_struct *struc)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if ((i = ft_strchr_index(struc->buf, '\n')) >= 0 && (!(struc->save_buf)))
	{
		*line = ft_strsub(struc->buf, 0, i);
		struc->save_buf = struc->buf[i + 1] ?
			ft_strdup(struc->buf + i + 1) : NULL;
		return (1);
	}
	else if (i >= 0 && struc->save_buf)
	{
		*line = ft_strsub(struc->buf, 0, i);
		tmp = ft_strjoin(struc->save_buf, *line);
		free(*line);
		*line = tmp;
		free(struc->save_buf);
		struc->save_buf = struc->buf[i + 1] ?
			ft_strdup(struc->buf + i + 1) : NULL;
		return (1);
	}
	return (0);
}

static int		get_read_line(char **line, t_struct **struc)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = NULL;
	while ((ret = read((*struc)->fd, (*struc)->buf, BUFF_SIZE)) > 0)
	{
		if (get_return_line(line, *struc) == 1)
			return (1);
		else
		{
			tmp = ft_strjoin((*struc)->save_buf, (*struc)->buf);
			free((*struc)->save_buf);
			(*struc)->save_buf = tmp;
		}
		ft_bzero((*struc)->buf, BUFF_SIZE);
	}
	if ((*struc)->save_buf != NULL && ret == 0)
	{
		*line = (*struc)->save_buf;
		(*struc)->save_buf = NULL;
		return (1);
	}
	return (ret < 0 ? -1 : 0);
}

int				get_next_line(int const fd, char **line)
{
	static t_struct	*struc = NULL;
	int				i;

	i = 0;
	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	get_create_line(fd, &struc);
	if (struc->save_buf != NULL &&
			(i = ft_strchr_index(struc->save_buf, '\n')) >= 0)
	{
		*line = ft_strsub(struc->save_buf, 0, i);
		ft_strcpy(struc->buf, struc->save_buf + i + 1);
		free(struc->save_buf);
		if (struc->buf[0])
			struc->save_buf = ft_strdup(struc->buf);
		else
		{
			struc->save_buf = NULL;
			free(struc->save_buf);
		}
		return (1);
	}
	return (get_read_line(line, &struc));
}
