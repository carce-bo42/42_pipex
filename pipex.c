#include "pipex.h"

void	arg_error(void)
{
	ft_pustr_fd("Usage: ./pipex file1 \"cmd1 flags1\" \"cmd2 flags2\" file2", 2);
	exit(0);
}

void	error_msg(void)
{
	char	*str;

	str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}

int		find_i_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*find_exec_path(char **argv, char **env)
{
	char	**exec_paths;
	int		i_path;

	i_path = find_i_path(env);





/* Point is, the child process will trick the cmd1 into having 
 * file1 as the STDIN (fd = 0), and write the output (fd = 1) on the
 * write end of the pipe, which the father process will be able to
 * read. This is achieved by duplicating the file1 fd on the
 * STDIN, and the STDOUT on the write end of the pipe. This way 
 * the parent process will read from the read end of the pipe
 * whatever the first cmd outputted. */
void	child(int p[2], char **argv, char **env)
{
	int		fd;
	char	**flags;
	char	*path;

	close(p[0]); 					//We dont need the read end of the pipe in the child process.
	fd = open(argv[1], O_RDONLY); 	// we open the archive given as an arg.
	if (fd == -1)
		error_msg();
	dup2(fd, 0); 		//Now STDIN means fd, so if cm1 needs some input it will interpret whatever fd has.
	dup2(p[1], 1); 		//Whatever execve does, it will be outputed to the write end of the pipe. 
	close(p[1]); 		// We no longer need the fd from p[1], we have it on STDOUT.
	path = find_exec_path(argv, env);
	cmd = ft_split(argv[2], ' ');
	if (execve(path, cmd, env) == -1)
		error_msg();
}

/*Program that copies the < file1 cmd1 | cmd2 > file2 bash command.*/
int main(int argc, char **argv, char **env)
{
	int		p[2];
	t_pid	pid;

	if (arg != 5)
		arg_error();
	if (pipe(p) == -1)
		error_msg();
	pid = fork();
	if (pid == -1)
		error_msg();
	if (pid == 0)
		child(p, argv, env);
	else
	{
		//Parent process;

	}
	return (0);
}
