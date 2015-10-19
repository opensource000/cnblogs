#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define READFD 0
#define WRITEFD 1

int main(int argc, char *argv[])
{
	int pipe_fd[2];
	pid_t pid;
	
	if (pipe(pipe_fd) < 0) 
	{
		printf("pipe create error\n");
		exit(1);
	}
	
	if ((pid = fork()) < 0 )
	{
		printf("fork error\n");
		exit(1);
	}

	// parent
	if (pid > 0) 
	{
		char buf_r[100];
		memset(buf_r, 0, sizeof(buf_r));
		
		close(pipe_fd[WRITEFD]);
		sleep(2);
		while (read(pipe_fd[0], buf_r, 100)) 
		{
			printf("print from parent ==> %s\n", buf_r);
		}
		close(pipe_fd[READFD]);
		exit(0);
	}
	else if (pid == 0) 
	{
		close(pipe_fd[READFD]);
		write(pipe_fd[WRITEFD], "Hello", 5);
		write(pipe_fd[WRITEFD], " Pipe", 5);
		close(pipe_fd[WRITEFD]);
		exit(0);
	}
	
	exit(0);
}
