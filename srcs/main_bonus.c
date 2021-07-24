#include "pipex_bonus.h"

static void	pipex_alpha(t_pip *p)
{
	int	pip[2];

	pipe(pip);
	p->pid = fork();
	if (p->pid == 0)
	{	
		file_input_piped_output(p, pip);
	}
	else
	{
		p->v_i = 3;
		if (p->v_i == p->argc - 2)
			piped_input_file_output(p, pip);
		else
			piped_input_piped_output(p, pip);
	}
}

static void	pipex_beta(t_pip *p)
{
	int	pip[2];

	pipe(pip);
	p->pid = fork();
	if (p->pid == 0)
	{
		close(pip[0]);
		here_doc_input(p, pip);
	}
	else
	{
		p->v_i = 3;
		hdoc_pipin_pipout(p, p->pid, pip);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pip	p;

	p.argc = argc;
	p.v_i = 2;
	p.argv = argv;
	p.env = env;
	p.fdi = dup(0);
	p.fdo = dup(1);
	if (argc < 5)
		print_usage_and_exit();
	else if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 8))
		pipex_alpha(&p);
	else if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8))
		pipex_beta(&p);
	else
		print_usage_and_exit();
	return (0);
}
