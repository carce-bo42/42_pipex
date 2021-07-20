#include "pipex.h"
#include "pipex_bonus.h"


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
	error_ctrl(argc);
}


