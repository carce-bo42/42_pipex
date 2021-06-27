#include "pipex.h"

void	arg_error(void)
{
	ft_putstr_fd(ANSI_COLOR_GREEN, 2);
	ft_putstr_fd("Usage: ./pipex file1 \"cmd1 flags1\" \"cmd2 flags2\" file2", 2);
	ft_putstr_fd(ANSI_UNSET_GREEN, 2);
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
