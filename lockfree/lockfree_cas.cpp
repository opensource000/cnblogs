#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>

int count = 0;

inline int CAS(unsigned long* mem, unsigned long oldval, unsigned long newval)
{
	__typeof (*mem) ret;
	// 这里测试的使用64位系统，如果是32位，这里使用cmpschgl
	__asm __volatile ("lock; cmpxchgq %2,%1"
						: "=a"(ret), "=m"(*mem)
						: "r"(newval), "m"(*mem), "0"(oldval));
	return ret==oldval;
}

void AtomicInc(int* addr)
{
	int oldval;
	int newval;
	do
	{
		oldval = *addr;
		newval = oldval+1;
	} while(!CAS((unsigned long*)addr, oldval, newval));
}

void *test_func(void *arg)
{
	int i=0;
	int confict = 0;
	for(i=0;i<2000000;++i)
	{
		AtomicInc(&count);
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
