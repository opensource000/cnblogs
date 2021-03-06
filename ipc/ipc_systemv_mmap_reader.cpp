#include <sys/mman.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct
{
	char name[32];
	int age;
} people;

int main(int argc, char** argv)
{
	int shm_id,i;
	key_t key;
	people* p_map;
	
	const char* name = "/dev/shm/my_systemv_shm1";
	key = ftok(name,0);
	if (key == -1)
	{
		perror("ftok error");
		return -1;
	}
	shm_id=shmget(key, 4096, IPC_CREAT);
	if(shm_id == -1)
	{
		perror("shmget error");
		return -1;
	}
	p_map=(people*)shmat(shm_id,NULL,0);
	
	for(int i = 0; i < 10; i++)
	{
		printf( "name:%s, ",(*(p_map+i)).name );
		printf( "age %d\n",(*(p_map+i)).age );
	}
	
	if(shmdt(p_map) == -1)
	{
		perror(" detach error ");
		return -1;
	}
	
	return 0;
}