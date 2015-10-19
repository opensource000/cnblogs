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
	unsigned int iprio;
	if (argc!=4)
	{
		printf("usage: ./ipc_posix_mq_send <mq name> <message> <priority>\n");
		exit(0);
	}
	iprio = atoi(argv[3]);
	
    mqID = mq_open(argv[optind], O_WRONLY);
    if (mqID < 0)
    {
        printf("open message queue %s error[%s]\n", argv[optind], strerror(errno));
        return -1;
    }
	printf("open message queue succ, mqID = %d\n", mqID);
	mq_send(mqID, argv[2], strlen(argv[2]), iprio);
	return 0;
}