#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

main(int argc, char** argv)
{
	int ret = shm_unlink(argv[1]);
	if (-1 == ret)
	{
		printf("unlink shm error = %s\n", strerror(errno));
		return -1;
	}
	
	printf("unlink ok \n");
	return 0;
}