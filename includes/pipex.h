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
#  define ANSI_COLOR_GREEN "\033[0;32m"
#  define ANSI_UNSET_GREEN "\033[0m"

int		find_i_path(char **env);
char	**put_bars_and_cmd_on_path(char **path, char **cmd);
char	**get_paths(char **cmd, char **env);
char	*find_exec_path(char **cmd, char **env);
void	free_matrix(char **mat);
void	error_msg_relative_to_file(char *file);
void	error_msg(void);
void	command_not_found_error(char **cmd);
void	arg_error(void);
void	wait_and_exit(pid_t pid);

// Libft utils

char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *src);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);

#endif
