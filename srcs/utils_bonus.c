#include "pipex_bonus.h"

void	call_execve(t_pip *p)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(p->argv[p->v_i], ' ');
	path = find_exec_path(cmd, p->env);
	if (execve(path, cmd, p->env) == -1)
		error_msg();
}

void	wait_free_and_exit(pid_t pid, t_pip *p)
{
	waitpid(pid, 0, 0);
	free(p);
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

void	print_usage_and_exit(void)
{
	ft_putstr_fd("pipex:\nusage: ___> ./pipex file1 \"cmd1 flags1\"  ...", 2);
	ft_putstr_fd("\"cmdn flags2\" file2\n       \\__> ./pipex here_doc ", 2);
	ft_putstr_fd("LIMITER \"cmd flags\" \"cmd1 flags1\" file\n", 2);
	exit(0);
}

size_t	max_len(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}
