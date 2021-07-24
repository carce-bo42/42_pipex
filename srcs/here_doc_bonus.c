#include "pipex_bonus.h"

void	hdoc_pipin_pipout(t_pip *p, pid_t pid_child, int old_pip[2])
{
	int		new_pip[2];

	close(old_pip[1]);
	waitpid(pid_child, 0, 0);
	pipe(new_pip);
	p->pid = fork();
	if (p->pid == 0)
	{
		dup_stdin_stdout_and_close(old_pip[0], new_pip[1]);
		call_execve(p);
	}
	else if (++(p->v_i) == p->argc - 2)
		pipin_file_append_out(p, new_pip);
	else
		pipin_pipout_append(p, new_pip);
}

void	pipin_file_append_out(t_pip *p, int pip[2])
{
	close(pip[1]);
	p->pid = fork();
	if (p->pid == 0)
	{
		p->fd = open(p->argv[p->v_i + 1], O_APPEND | O_WRONLY | O_CREAT, 00644);
		dup_stdin_stdout_and_close(pip[0], p->fd);
		call_execve(p);
	}
	else
		wait_free_and_exit(p->pid, p);
}

void	pipin_pipout_append(t_pip *p, int old_pip[2])
{
	int		new_pip[2];

	pipe(new_pip);
	close(old_pip[1]);
	p->pid = fork();
	if (p->pid == 0)
	{
		dup_stdin_stdout_and_close(old_pip[0], new_pip[1]);
		call_execve(p);
	}
	else if (++(p->v_i) == p->argc - 2)
		pipin_file_append_out(p, new_pip);
	else
		pipin_pipout_append(p, new_pip);
}

void	here_doc_input(t_pip *p, int pip[2])
{
	char	*line;

	write(1, "$> ", 3);
	get_next_line(0, &line);
	if (!ft_strncmp(line, p->argv[2], max_len(line, p->argv[2])))
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
