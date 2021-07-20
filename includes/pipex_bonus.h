/* Bonus functions */




typedef struct	s_pip
{
	int		p[2];
	int		argv_idx;
	char	***argv_p;
	char	***env_p;
	pid_t	child;
}				t_pip;
