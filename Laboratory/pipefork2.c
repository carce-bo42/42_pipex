#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void	forkiar()
{
	printf("\n\nA\n\n");
    printf("First printf:%i PID:%i\n", fork(), getpid());
	wait(0);
}

void	forkiar2()
{
    printf("Second printf:%i PID:%i\n", fork(), getpid());
}
	

int main()
{
    // make two process which run same
    // program after this instruction
	forkiar();
	forkiar2();
    /*printf("First printf:%i PID:%i\n", fork(), getpid());
	printf("Esto solo se imprimira por pantalla 2 vecesAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\n\n\n\n\n\n\n");
    printf("Second printf:%i PID:%i\n", fork(), getpid());
    printf("First printf:%i PID:%i\n", fork(), getpid());
    printf("Second printf:%i PID:%i\n", fork(), getpid());
    printf("First printf:%i PID:%i\n", fork(), getpid());
   	//printf("Third printf:%i\n", fork());
    printf("Hello world! PID:%i\n", getpid());*/
    return 0;
}
