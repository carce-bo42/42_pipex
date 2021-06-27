#include "pipex.h"

void	arg_error(void)
{
	ft_putstr_fd("Usage: ./pipex file1 \"cmd1 flags1\" \"cmd2 flags2\" file2", 2);
	exit(0);
}

void	command_not_found_error(char **cmd)
{
	ft_putstr_fd("pipex: Command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
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

void	error_msg_explicit(char *file)
{
	char	*str;

	str = strerror(errno);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
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

char	**put_bars_and_cmd_on_path(char **path, char **cmd)
{
	int		i;
	char	*aux_1;
	char	*aux_2;

	i = 0;
	while (path[i])
	{
		aux_1 = path[i];
		path[i] = ft_strjoin(path[i], "/");
		aux_2 = path[i];
		path[i] = ft_strjoin(path[i], cmd[0]);
		free(aux_1);
		free(aux_2);
		i++;
	}
	return (path);
}

char	**get_paths(char **cmd, char **env)
{
	int		i_path;
	char	*aux;
	char	**paths_wo_bar;

	i_path = find_i_path(env);
	aux = ft_strtrim(env[i_path], "PATH=");
	paths_wo_bar = ft_split(aux, ':');
	free(aux);
	return (put_bars_and_cmd_on_path(paths_wo_bar, cmd));
}

void	free_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat[i]);
	free(mat);
}

/*Function that will get the correct path to the binary command
 * specified by cmd (the <0 entries of this matrix are the corresponding
 * flags if specified). It first gets every path in the PATH env variable,
 * then it adds a / and the exec name to form the correct path (if it
 * exists), and then checks with access(2) wether there is one path
 * that can find the binary, and in that case it returns it.*/
char	*find_exec_path(char **cmd, char **env)
{
	char	**exec_paths;
	char	*path;
	int		i;

	exec_paths = get_paths(cmd, env);
	path = NULL;
	i = 0;
	while (exec_paths[i])
	{
		if (access(exec_paths[i], X_OK | F_OK) == 0)
		{
			path = ft_strdup(exec_paths[i]);
			break ;
		}
		i++;
	}
	free_matrix(exec_paths);
	if (!path)
		command_not_found_error(cmd);
	return (path);
}

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
	char	*path;
	char	**cmd;

	close(p[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_msg_explicit(argv[1]);
	dup2(fd, 0);
	dup2(p[1], 1);
	close(p[1]);
	cmd = ft_split(argv[2], ' ');
	path = find_exec_path(cmd, env);
	if (execve(path, cmd, env) == -1)
		error_msg();
}

void	parent(int p[2], char **argv, char **env)
{
	int		fd;
	char	*path;
	char	**cmd;
		
	close(p[1]);
	fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		error_msg();
	dup2(p[0], 0);
	dup2(fd, 1);
	close(p[0]);
	cmd = ft_split(argv[3], ' ');
	path = find_exec_path(cmd, env);
	if (execve(path, cmd, env) == -1)
		error_msg();
}

/*Program that copies the < file1 cmd1 | cmd2 > file2 bash command.*/
int main(int argc, char **argv, char **env)
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
		parent(p, argv, env);
	return (0);
}
