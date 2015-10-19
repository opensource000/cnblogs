#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char** argv)  
{    
    int msgid = -1;   
    
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666);  
    if(msgid == -1)  
    {  
        printf("msgget failed with error: %s\n", strerror(errno));  
        return -1;
    }
	printf("msgget succ, msgid = %d\n", msgid);
	
	if (msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        printf("msgctl IPC_RMID failed\n");  
        return -1;
    }  
    
	return 0;
}  
