#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\nPass command line argument as your filename.\n");
		return 1;
	}
	pid_t pid;
	pid = fork();

	if (pid == 0)
	{
		FILE *stream;
		int i;
		stream = fopen(argv[1], "w");
		if (!stream)
		{
			printf("\nError while opening file\n");
			return 1;	
		}
		else
		{
		
			for ( i = 1; i <= 50; i++)
			{
				if(i % 3 == 0)
					fprintf(stream, "%d\n", i);
			}
			fclose(stream);
		}
	}
	if (pid != 0)
	{
		int *wstatus;
		wait(wstatus);
		printf("\nPARENT PID: %d", getpid());
		printf("\nCHILD PID: %d", pid);
		printf("\nProgram ended.\n");
	}
	//można tu użyć O_APPEND i wtedy raczej nie używać lseeka, ale tak imo lepiej
	int fd = open(argv[1], O_RDONLY);
	int size = lseek(fd, 0, SEEK_END);
	printf("%d\n", size);
	return 0;
}
