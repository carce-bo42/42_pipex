# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>

int main()
{
	int fd;


	//fd = open("A.txt", O_WRONLY);
	//if (fd != -1)
	//unlink("A.txt");
	fd = open("A.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	write(fd, "hello", 5);
	close(fd);
	return (0);
}

