#include "pipex.h"

/* Bonus functions */

typedef struct	s_pip
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
void	pipex_alpha(t_pip *p);
void	pipex_beta(t_pip *p);
void	dup_stdin_stdout_and_close(int new_in, int new_out);
void	file_input_piped_output(t_pip *p, int pip[2]);
void	piped_input_file_output(t_pip *p, pid_t pid_child, int pip[2]);
void	piped_input_piped_output(t_pip *p, pid_t child, int old_pip[2]);
