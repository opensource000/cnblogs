#include <iostream>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

using namespace std;

int main(int argc, char** argv)
{
    mqd_t mqID;
	if (argc!=4)
	{
		printf("usage: ./ipc_posix_mq_open_setattr <mq name> <max msg> <msgsize>\n");
		exit(0);
	}
	
	mq_attr mqAttr;
	mqAttr.mq_maxmsg = atoi(argv[2]);
	mqAttr.mq_msgsize = atoi(argv[3]);
	
    mqID = mq_open(argv[optind], O_RDWR|O_CREAT|O_EXCL, 0666, &mqAttr);
    if (mqID < 0)
    {
        printf("open message queue %s error[%s]\n", argv[optind], strerror(errno));
        return -1;
    }
	printf("open message queue succ, mqID = %d\n", mqID);
	
    if (mq_getattr(mqID, &mqAttr) < 0)
    {
		printf("get the message queue attribute error\n");
        return -1;
    }
	
	printf("mq_flags = %d, mq_maxmsg = %d, mq_msgsize = %d, mq_curmsgs = %d\n",
		mqAttr.mq_flags, mqAttr.mq_maxmsg, mqAttr.mq_msgsize, mqAttr.mq_curmsgs);
	mq_close(mqID);
	
	return 0;
}