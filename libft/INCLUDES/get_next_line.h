/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 18:24:44 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/14 14:40:42 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>

typedef struct		s_struct
{
	int				fd;
	char			buf[BUFF_SIZE + 1];
	char			*save_buf;
	struct s_struct	*next;
}					t_struct;

int					get_next_line(int const fd, char **line);

#endif
