#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_barrier_t barrier;
int thread_num = 10;

void* doSomething(void* arg)
{
	printf("before wait %d\n", pthread_self());
	pthread_barrier_wait(&barrier);//所有线程都被阻塞在这里
	printf("I'm in pthread %d\n", pthread_self()); 
	
	return NULL;
}

int activate()
{ 
	//等一切都安排好了调用该函数。起跑枪“砰！”
	pthread_barrier_wait(&barrier);
	return 0;
}

int main(int argc, char** argv)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_t* thread = (pthread_t*)malloc(thread_num * sizeof(pthread_t));
	pthread_barrier_init(&barrier, NULL, thread_num + 1);
	for(int i = 0; i < thread_num; i++)
	{
		pthread_create(thread+i, &attr, doSomething, NULL);
	}
	
	activate();
	
	for (int i = 0; i < thread_num; i++)
	{
		pthread_join(*(thread+i),NULL);
	}

	pthread_attr_destroy(&attr);
	
	return 0;
}
