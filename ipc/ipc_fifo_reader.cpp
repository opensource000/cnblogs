#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <limits.h>  
#include <string.h>  
  
int main(int argc, char** argv)  
{  
    const char *fifo_name = "/tmp/my_fifo";  
    int pipe_fd = -1;  
    int res = 0;  
    int open_mode = O_RDONLY;  
    char buffer[PIPE_BUF + 1];  
    int bytes_read = 0;  
    
    //��ջ�������  
    memset(buffer, '\0', sizeof(buffer));  
	
	 if(access(fifo_name, F_OK) == -1)  
    {  
        //�ܵ��ļ�������  
        //���������ܵ�  
        res = mkfifo(fifo_name, 0777);  
        if(res != 0)  
        {  
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);  
            exit(EXIT_FAILURE);  
        }  
    }  
  
    printf("Process %d opening FIFO O_RDONLY\n", getpid());  
    //��ֻ��������ʽ�򿪹ܵ��ļ���ע����fifowrite.c�ļ��е�FIFOͬ��  
    pipe_fd = open(fifo_name, open_mode);  
    printf("Process %d result %d\n",getpid(), pipe_fd);  
    sleep(3); //����sleepһ�£��ȵ�д����д����
    if (pipe_fd != -1)  
    {
		//��ȡFIFO�е�����  
		res = read(pipe_fd, buffer, PIPE_BUF);
		bytes_read += res;
		printf("get data %s \n", buffer);  
        
        close(pipe_fd);
    }  
    else  
	{
        exit(EXIT_FAILURE);  
	}
  
    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);  
    exit(EXIT_SUCCESS);  
}  
