#ifndef FT_P_H
# define FT_P_H
#include <libft.h>
#include <shared.h>
#include <get_next_line.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>

/*
** Server
*/

void    cmd_ls(int fd, char *arg);
void    cmd_cd(int fd, char *arg, char *absolute_path);
void	cmd_pwd(int fd);
void	cmd_mkdir(int fd, char *arg);

/*
** Client
*/

void    cmd_lls(char *arg);
void    cmd_lcd(char *arg, char *absolute_path);
void	cmd_lpwd();
void	cmd_lmkdir(char *arg);

#endif