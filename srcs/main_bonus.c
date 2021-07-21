#include "pipex.h"
#include "pipex_bonus.h"

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
	dup2(new_in, 0);
	close(new_in);
	dup2(new_out, 1);
	close(new_out);
}

void	file_input_piped_output(t_pip *p, int pip[2])
{
	char	*path;
	char	**cmd;

	close(pip[0]);
	p->fd = open(p->argv[1], O_RDONLY);
	if (p->fd == -1)
		error_msg_relative_to_file(p->argv[1]);
	dup_stdin_stdout_and_close(p->fd, pip[1]);
	cmd = ft_split(p->argv[2], ' ');
	path = find_exec_path(cmd, p->env);
	if (execve(path, cmd, p->env) == -1)
	   error_msg();
}

void	piped_input_file_output(t_pip *p, pid_t pid_child, int pip[2])
{
	char	**cmd;
	char	*path;

	p->pid = fork();
	close(pip[1]);
	if (p->pid == 0)
	{
		waitpid(pid_child, 0, WNOHANG);
		p->fd = open(p->argv[v_i + 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (p->fd == -1)
			error_msg_relative_to_file(p->argv[v_i + 1]);
		dup_stdin_stdout_and_close(pip[0], p->fd); 
		cmd = ft_split(p->argv[p->v_i], ' ');
		path = find_exec_path(cmd, env);
		if (execve(path, cmd, env) == -1)
			error_msg();
	}
	else
		wait_and_exit(p->pid);
}

void	piped_input_piped_output(t_pip *p, pid_t pid_child, int old_pip[2])
{
	int		new_pip[2];
	char	**cmd;
	char	*path;

	pipe(new_pip);
	p->pid = fork();
	close(old_pip[1]);
	if (p->pid == 0)
	{
		waitpid(pid_child, 0, WNOHANG);
		dup_stdin_stdout_and_close(old_pip[0], new_pip[1]); 
		cmd = ft_split(p->argv[p->v_i], ' ');
		path = find_exec_path(cmd, env);
		if (execve(path, cmd, env) == -1)
			error_msg();
	}
	else if (++(p->v_i) == p->argc - 3)
		piped_input_file_output(p, p->pid, new_pip);
	else
		piped_input_piped_output(p, p->pid, new_pip);
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
		if (p->v_i == p->argc - 3)
			piped_input_file_output(p, p->pid, pip);
		else
			piped_input_piped_output(p, p->pid, pip);
	}
}

void	init_struct(t_pip *p, int argc, char **argv, char **env)
{
	p->argc = argc;
	p->v_i = argc - 1;
	p->argv = argv;
	p->env = env;
	p->fdi = dup(0);
	p->fdo = dup(1);
}

int main(int argc, char **argv, char **env)
{
	t_pip	p;

	init_struct(&p);
	if (argc < 5)
		print_usage_and_exit();
	else if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 8))
		pipex_alpha(&p);
	else if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8))
		/*pipex_beta(&p)*/;
	else
		print_usage_and_exit();
	return (0);
}
