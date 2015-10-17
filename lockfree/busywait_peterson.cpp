#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>

int count = 0;
#define N 2
volatile int turn;   
volatile int interested[N] = {0}; 


void enter_region(int process)
{
	int other = 1 - process; //另一个进程  
	interested[process] = true;
	turn = process;
	while (turn == process && interested[other] == true) NULL; //一直循环，直到other进程退出临界区  
}

void leave_region(int process)
{
	interested[process] = false; 	// leave critical region
}

void *test_func(void *arg)
{
	int process = *((int *)arg);
	printf("thread %d run\n", process);
	int i=0;
	for(i=0;i<2000000;++i)
	{
		enter_region(process);
		//printf("%d enter, count = %d\n", pthread_self(),count);
		++count;
		leave_region(process);
	}
	return NULL;
}

int main(int argc, const char *argv[])
{
	pthread_t id[N];
	int process[N];
	int i = 0;

	uint64_t usetime;
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start,NULL);
	for(i=0;i<N;++i)
	{
		process[i] = i;
	}	
	
	for(i=0;i<N;++i)
	{
		pthread_create(&id[i],NULL,test_func,&process[i]);
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
