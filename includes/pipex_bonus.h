#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "pipex.h"

/* Bonus functions */

typedef struct s_pip
{
	int		fd;
	int		v_i;
	int		argc;
	int		fdi;
	int		fdo;
	char	**argv;
	char	**env;
	pid_t	pid;
}				t_pip;

void	print_usage_and_exit(void);
void	dup_stdin_stdout_and_close(int new_in, int new_out);
void	file_input_piped_output(t_pip *p, int pip[2]);
void	piped_input_file_output(t_pip *p, int pip[2]);
void	piped_input_piped_output(t_pip *p, int old_pip[2]);
void	here_doc_input(t_pip *p, int pip[2]);
void	hdoc_pipin_pipout(t_pip *p, pid_t pid_child, int old_pip[2]);
void	pipin_file_append_out(t_pip *p, int pip[2]);
void	pipin_pipout_append(t_pip *p, int old_pip[2]);
void	call_execve(t_pip *p);
size_t	max_len(const char *s1, const char *s2);

// Gnl utils

# define BUFFER_SIZE 100

char	*ft_strjoin_n_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);

#endif
