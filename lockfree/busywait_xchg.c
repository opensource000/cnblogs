#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <asm/system.h>
#include <sys/time.h>
#include <stdint.h>

volatile int in_using = 0;
int count = 0;
#define N 2

void enter_region()
{
	while (xchg(&in_using, 1)) NULL;
}

void leave_region()
{
	in_using = 0;	// leave critical region
}

void *test_func(void *arg)
{
	int i=0;
	for(i=0;i<2000000;++i)
	{
		enter_region();
		++count;
		leave_region();
	}
	
	return NULL;
}

int main(int argc, const char *argv[])
{
	pthread_t id[20];
	int i = 0;

	uint64_t usetime;
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start,NULL);
	
	for(i=0;i<N;++i)
	{
		pthread_create(&id[i],NULL,test_func,NULL);
	}

	for(i=0;i<N;++i)
	{
		pthread_join(id[i],NULL);
	}
	
	gettimeofday(&end,NULL);

	usetime = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
	printf("count = %d, usetime = %lu usecs\n", count, usetime);
	return 0;
}
