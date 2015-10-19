#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

typedef struct
{
	char name[32];
	int age;
} people;

main(int argc, char** argv)
{
	people* p_map;
	struct stat filestat;
	
	int fd = open(argv[1], O_CREAT|O_RDWR, 00777);
	if (-1 == fd)
	{
		printf("open file error = %s\n", strerror(errno));
		return -1;
	}
	fstat(fd, &filestat);
	p_map = (people*)mmap(NULL, filestat.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == p_map)
	{
		printf("mmap file error = %s\n", strerror(errno));
		return -1;
	}
	
	for(int i = 0; i < 10; i++)
	{
		printf("name = %s, age = %d\n",(*(p_map+i)).name, (*(p_map+i)).age);
	}
	
	close(fd);
	munmap(p_map, sizeof(people)*10);
	printf("umap ok \n");
	return 0;
}