#include "pipex.h"

int main()
{
	int	p[2];
	int	p1[2];
	pid_t	pid;
	char	buf[100];

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
		write(1, "hey wusup\n", 10);
		exit(0);
	}
	else
	{
		close(p[1]);
		waitpid(pid, 0, 0);
		read(p[0], buf, 10);
		buf[10] = '\0';
		printf("this is the buffer: %s", buf);
		pipe(p1);
		pid = fork();
		if (pid == 0)
		{
			close(p1[0]);
			dup2(p1[1], 1);
			close(p1[1]);
			write(1, "hey wussup two\n", 14);
			exit(0);
		}
		else
		{
			close(p1[1]);
			waitpid(pid, 0, 0);
			read(p1[0], buf, 14);
			buf[14] = '\0';
			printf("this is the 2 buffer: %s", buf);
			exit(0);
		}
	}
	printf("No one ever will read this\n");	
	return(0);
}

