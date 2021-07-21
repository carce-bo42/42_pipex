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
