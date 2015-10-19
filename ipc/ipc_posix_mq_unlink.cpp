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
		printf("usage: ./ipc_posix_mq_unlink <mq name>\n");
		exit(0);
	}
	
    mq_unlink(argv[optind]);
	printf("error = %s\n", strerror(errno));
	return 0;
}
