#include "pipex_bonus.h"

void	file_input_piped_output(t_pip *p, int pip[2])
{
	close(pip[0]);
	p->fd = open(p->argv[1], O_RDONLY);
	if (p->fd == -1)
		error_msg_relative_to_file(p->argv[1]);
	dup_stdin_stdout_and_close(p->fd, pip[1]);
	call_execve(p);
}

void	piped_input_file_output(t_pip *p, int pip[2])
{
	close(pip[1]);
	p->pid = fork();
	if (p->pid == 0)
	{
		p->fd = open(p->argv[p->argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 00644);
		dup_stdin_stdout_and_close(pip[0], p->fd);
		call_execve(p);
	}
	else
		wait_free_and_exit(p->pid, p);
}

void	piped_input_piped_output(t_pip *p, int old_pip[2])
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
		piped_input_file_output(p, new_pip);
	else
		piped_input_piped_output(p, new_pip);
}
