#include "pipex.h"

static void	wait_and_exit(pid_t pid)
{
	waitpid(pid, 0, 0);
	exit(0);
}

/* Point is, the child process will trick the cmd1 into having 
 * file1 as the STDIN (fd = 0), and write the output (fd = 1) on the
 * write end of the pipe, which the father process will be able to
 * read. This is achieved by duplicating the file1 fd on the
 * STDIN, and the STDOUT on the write end of the pipe. This way 
 * the parent process will read from the read end of the pipe
 * whatever the first cmd outputted. */
static void	child(int p[2], char **argv, char **env)
{
	int		fd;
	char	*path;
	char	**cmd;

	close(p[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_msg_relative_to_file(argv[1]);
	dup2(fd, 0);
	dup2(p[1], 1);
	close(p[1]);
	cmd = ft_split(argv[2], ' ');
	path = find_exec_path(cmd, env);
	if (execve(path, cmd, env) == -1)
		error_msg();
}

/*In this case, the parent will recieve on the stdin whatever the
 * child process outputted, and it will ovewrite (O_TRUNC) or create
 * a new file whose fd will be duplicated with the STDOUT of the
 * parent process.*/
static void	parent(int p[2], char **argv, char **env, pid_t pid_child)
{
	int		fd;
	char	*path;
	pid_t	pid;
	char	**cmd;

	pid = fork();
	close(p[1]);
	if (pid == 0)
	{
		waitpid(pid_child, 0, 0);
		fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (fd == -1)
			error_msg_relative_to_file(argv[4]);
		cmd = ft_split(argv[3], ' ');
		path = find_exec_path(ft_split(argv[3], ' '), env);
		dup2(p[0], 0);
		dup2(fd, 1);
		close(p[0]);
		if (execve(path, cmd, env) == -1)
			error_msg();
	}
	else
		wait_and_exit(pid);
}

/*Program that copies the < file1 cmd1 | cmd2 > file2 bash command.*/
int	main(int argc, char **argv, char **env)
{
	int		p[2];
	pid_t	pid;

	if (argc != 5)
		arg_error();
	if (pipe(p) == -1)
		error_msg();
	pid = fork();
	if (pid == -1)
		error_msg();
	if (pid == 0)
		child(p, argv, env);
	else
		parent(p, argv, env, pid);
	return (0);
}
