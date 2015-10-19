#include <unistd.h>  
#include <stdlib.h>  
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <stdio.h>  
#include <string.h>  
  
int main(int argc, char** argv)
{  
    const char *fifo_name = "/tmp/my_fifo";  
    int pipe_fd = -1;    
    int res = 0;  
    const int open_mode = O_WRONLY;  
     
    if(access(fifo_name, F_OK) == -1)  
    {  
        //管道文件不存在  
        //创建命名管道  
        res = mkfifo(fifo_name, 0777);  
        if(res != 0)  
        {  
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);  
            exit(EXIT_FAILURE);  
        }  
    }  
  
    printf("Process %d opening FIFO O_WRONLY\n", getpid());  
    //以只写阻塞方式打开FIFO文件，以只读方式打开数据文件  
    pipe_fd = open(fifo_name, open_mode);  
    printf("Process %d result %d\n", getpid(), pipe_fd);  
  
    if(pipe_fd != -1)  
    {  
		write(pipe_fd, "hello", 5);
		write(pipe_fd, " fifo", 5);
		printf("Process write finished\n", getpid());  
        close(pipe_fd);
    }  
    else
	{
        exit(EXIT_FAILURE);  
	}
    printf("Process %d finished\n", getpid());  
    exit(EXIT_SUCCESS);  
}  
