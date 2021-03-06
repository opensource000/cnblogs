#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <asm/system.h>
#include <sys/time.h>
#include <stdint.h>

int count = 0;

int fetch_and_add(int* i, int value, int* confict)
{
	int old_value;
	int new_value;
	int v;
	do 
	{
		old_value = *i;
		new_value = old_value + 1;
		v = cmpxchg(i, old_value, new_value);
		(*confict)++;
	} while (old_value != v);
}

void *test_func(void *arg)
{
	int i=0;
	int confict = 0;
	for(i=0;i<2000000;++i)
	{
		fetch_and_add(&count,1,&confict);
		//__sync_fetch_and_add(&count,1);
	}
	printf("[%d]confict = %d\n", pthread_self(), confict);
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
	
	for(i=0;i<20;++i)
	{
		pthread_create(&id[i],NULL,test_func,NULL);
	}

	for(i=0;i<20;++i)
	{
		pthread_join(id[i],NULL);
	}
	
	gettimeofday(&end,NULL);

	usetime = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
	printf("count = %d, usetime = %lu usecs\n", count, usetime);
	return 0;
}
