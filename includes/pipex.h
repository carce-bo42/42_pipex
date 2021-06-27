#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# ifndef ANSI_COLOR_GREEN
#  define ANSI_COLOR_GREEN "\033[0;32m"
# endif
# ifndef ANSI_UNSET_GREEN
#  define ANSI_UNSET_GREEN "\033[0m"
# endif
int		find_i_path(char **env);
char	**put_bars_and_cmd_on_path(char **path, char **cmd);
char	**get_paths(char **cmd, char **env);
char	*find_exec_path(char **cmd, char **env);
void	free_matrix(char **mat);
void	error_msg_explicit(char *file);
void	error_msg(void);
void	command_not_found_error(char **cmd);
void	arg_error(void);
#endif
