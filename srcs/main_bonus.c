#include "pipex_bonus.h"

void	wait_and_exit(pid_t pid)
{
	waitpid(pid, 0, 0);
	exit(0);
}

void	print_usage_and_exit(void)
{
	ft_putstr_fd("pipex:\nusage: ___> ./pipex file1 \"cmd1 flags1\"  ...", 2);
	ft_putstr_fd("\"cmdn flags2\" file2\n       \\__> ./pipex here_doc ", 2);
	ft_putstr_fd("LIMITER \"cmd flags\" \"cmd1 flags\" file\n", 2);
	exit(0);
}

/* Function that comes in VERY handy when working with pipes. It
 * duplicates the STDIN fildescriptor to some new_in, and does the
 * same for STDOUT, then proceeds to close these new_in/new_out fd's,
 * since they are now accessible through 0 and 1, respectively.*/
void	dup_stdin_stdout_and_close(int new_in, int new_out)
{
	if (dup2(new_in, 0) == -1)
		error_msg();
	close(new_in);
	if (dup2(new_out, 1) == -1)
		error_msg();
	close(new_out);
}

void	pipex_alpha(t_pip *p)
{
	int	pip[2];

	pipe(pip);
	p->pid = fork();
	if (p->pid == 0)
		file_input_piped_output(p, pip);
	else
	{
		p->v_i = 3;
		if (p->v_i == p->argc - 2)
			piped_input_file_output(p, p->pid, pip);
		else
			piped_input_piped_output(p, p->pid, pip);
	}
}

void	here_doc_input(t_pip *p, int pip[2])
{
	char	*line;

	p->fdi = 0;
	close(pip[0]);
	line = NULL;
	write(1, "$> ", 3);
	get_next_line(0, &line);
	if (ft_strnstr(line, p->argv[2], ft_strlen(line)))
	{
		free(line);
		close(pip[1]);
		exit(0);
	}
	else
	{
		write(pip[1], line, ft_strlen(line));
		write(pip[1], "\n", 1);
		free(line);
		here_doc_input(p, pip);
	}
}

void	pipex_beta(t_pip *p)
{
	int	pip[2];

	pipe(pip);
	p->pid = fork();
	if (p->pid == 0)
		here_doc_input(p, pip);
	else
	{
		p->v_i = 3;
		piped_input_piped_output(p, p->pid, pip);
	}
}

int main(int argc, char **argv, char **env)
{
	t_pip	p;

	p.argc = argc;
	p.v_i = argc - 1;
	p.argv = argv;
	p.env = env;
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
