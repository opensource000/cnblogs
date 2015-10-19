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
	mq_attr mqAttr;
	unsigned int iprio;
	unsigned int n;
	char buff[8192];
	
	if (argc!=2)
	{
		printf("usage: ./ipc_posix_mq_recv <mq name>\n");
		exit(0);
	}
	
	mqID = mq_open(argv[optind], O_RDONLY);
    if (mqID < 0)
    {
        printf("open message queue %s error[%s]\n", argv[optind], strerror(errno));
        return -1;
    }
	mq_getattr(mqID, &mqAttr);
	n = mq_receive(mqID, buff, mqAttr.mq_msgsize, &iprio);
	printf("read from mq`s msg = %s\n", buff);
	return 0;
}