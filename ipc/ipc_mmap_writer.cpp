#include <sys/mman.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct
{
	char name[32];
	int age;
} people;

main(int argc, char** argv)
{
	people* p_map;
	char temp = 'a';
	
	int fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, 00777);
	if (-1 == fd)
	{
		printf("open file error = %s\n", strerror(errno));
		return -1;
	}
	ftruncate(fd, sizeof(people)*10);
	p_map = (people*)mmap(NULL, sizeof(people)*10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == p_map)
	{
		printf("mmap file error = %s\n", strerror(errno));
		return -1;
	}
	
	for(int i = 0; i < 10; i++)
	{
		memcpy( ( *(p_map+i) ).name, &temp, 1);
		( *(p_map+i) ).name[1] = 0;
		( *(p_map+i) ).age = 20+i;
		temp += 1;
	}
	printf("initialize over\n");
		
	close(fd);
	munmap(p_map, sizeof(people)*10);
	printf("umap ok \n");
	return 0;
}