#include "pipex.h"
#include "pipex_bonus.h"

void	print_usage_and _exit(void)
{
	ft_putstr_fd("pipex:\nusage: ___> ./pipex file1 \"cmd1 flags1\"  ...", 2);
	ft_putstr_fd("\"cmdn flags2\" file2\n       \\__> ./pipex here_doc ", 2);
	ft_putstr_fd("LIMITER \"cmd flags\" \"cmd1 flags\" file\n", 2);
	exit(0);
}

/*Arbitrary function that carries an in between pipe. 
 * duplicates the 0 into the read end of the pipe p[0], 
 * and the 1 into the write end, so the pipeing process can
 * keep going.*/
void	nth_process(int p[2], char **argv, char **env, pid_t child)
{
	pid_t	pid;

	pid = fork();
	close();
}

int main(int argc, char **argv, char **env)
{
	if (argc == 1)
		print_usage_and_exit();
	else if (argc > 5 && ft_strncmp(argv[1], "here_doc"))
		pipex_alpha(argc, argv, env);
	else if (argc == 6 && !ft_strncmp(argv[1], "here_doc"))
		pipex_beta(argc, argv, env);
	else
		print_usage_and_exit();
	return (0);
}
