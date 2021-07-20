/* Bonus functions */

typedef struct	s_pip
{
	int		p[2];
	int		argv_idx;
	char	***argv_p;
	char	***env_p;
	pid_t	child;
}				t_pip;

void	print_usage_and_exit(void);
void	pipex_alpha(int argc, char **argv, char **env);
void	pipex_beta(int argc, char **argv, char **env);
