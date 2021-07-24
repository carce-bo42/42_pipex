#include "pipex_bonus.h"

static void	pipex_alpha(t_pip *p)
{
	int	pip[2];

	pipe(pip);
	p->pid = fork();
	printf("p[0] = %i, p[1] = %i\n", pip[0], pip[1]);
	if (p->pid == 0)
		file_input_piped_output(p, pip);
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

t_pip	*init_pipe_struct(int argc, char **argv, char **env)
{
	t_pip	*p;

	p = malloc(sizeof(t_pip));
	p->argc = argc;
	p->v_i = 2;
	p->argv = argv;
	p->env = env;
	p->fdi = dup(0);
	p->fdo = dup(1);
	return (p);
}

int	main(int argc, char **argv, char **env)
{
	t_pip	*p;
	char	*hdoc;

	p = init_pipe_struct(argc, argv, env);
	hdoc = "here_doc";
	if (argc < 5)
		print_usage_and_exit();
	else if (argc >= 5 && ft_strncmp(argv[1], hdoc, max_len(argv[1], hdoc)))
		pipex_alpha(p);
	else if (argc >= 6 && !ft_strncmp(argv[1], hdoc, max_len(argv[1], hdoc)))
		pipex_beta(p);
	else
		print_usage_and_exit();
	return (0);
}
