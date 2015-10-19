#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFF_SIZE 1024
struct mq_msg_st  
{  
    long msg_type;  
    char text[BUFF_SIZE];  
};

int main(int argc, char** argv)  
{    
    int msgid = -1;  
	struct mq_msg_st data;
    long msgtype = 0;
	int iret = 0;
  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666);  
    if(msgid == -1)  
    {  
        printf("msgget failed with error: %s\n", strerror(errno));  
        return -1;
    }
	printf("msgget succ, msgid = %d\n", msgid);
	
	// 获取消息队列状态
	struct msqid_ds ds;
    iret = msgctl(msgid, IPC_STAT, (struct msqid_ds *)&ds);
    if(iret == -1)
    {
        printf("msgctl IPC_STAT failed\n");
        return -2;
    }
	
    //从队列中获取消息，直到遇到end消息为止  
    while(1)
    {
		iret = msgrcv(msgid, (void*)&data, BUFF_SIZE, msgtype, IPC_NOWAIT);
        if (iret == -1)
        {  
			if (errno == ENOMSG)
			{
				usleep(100);
				continue;
			}
			else
			{
				printf("msgrcv failed, error = %s\n", strerror(errno));
				return -1;
			}
        }
		
        printf("get message: %s\n", data.text);  
        //遇到end结束  
        if(strncmp(data.text, "end", 3) == 0)
		{
			break;
		}  
    }
	
    return 0;
}  
