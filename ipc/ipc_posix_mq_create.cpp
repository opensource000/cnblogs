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
	if (argc!=2)
	{
		printf("usage: ./ipc_posix_mq_create <mq name>\n");
		exit(0);
	}
	
    mqID = mq_open(argv[optind], O_RDWR|O_CREAT|O_EXCL, 0666, NULL);
    if (mqID < 0)
    {
        printf("open message queue %s error[%s]\n", argv[optind], strerror(errno));
        return -1;
    }
	printf("open message queue succ, mqID = %d\n", mqID);
	
    mq_attr mqAttr;
    if (mq_getattr(mqID, &mqAttr) < 0)
    {
		printf("get the message queue attribute error\n");
        return -1;
    }
	
	printf("mq_flags = %d, mq_maxmsg = %d, mq_msgsize = %d, mq_curmsgs = %d\n",
		mqAttr.mq_flags, mqAttr.mq_maxmsg, mqAttr.mq_msgsize, mqAttr.mq_curmsgs);
	
	return 0;
}