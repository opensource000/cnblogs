#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int currentidx = 0;
char* str[2] = {0};

void* consume(void *arg)
{
	sleep(1);
    while(1)
    {
        printf("************************consumed %s, index %d, self %d\n",str[currentidx], currentidx, pthread_self());
        sleep(1); 
    }
    
    return NULL;
}

void* produce( void * arg )
{
	const char* s_str1 = "hello";
	const char* s_str2 = "world";
	
    while(1)
    {
		printf("product begin\n");
		
		// read copy
        int other = 1 - currentidx;
		str[other] = (char*)malloc(6);
		if (other == 0)
		{
			strncpy(str[other], s_str1, 6);
		}
		else
		{
			strncpy(str[other], s_str2, 6);
		}
		
		// update 原子的修改索引
		currentidx = other;
		// delete old currentidx
		free(str[1-currentidx]);
        sleep(5);
    }
    
    return NULL;
}

int main( void )
{
    pthread_t thread1,thread2;
    pthread_create(&thread1, NULL, &produce, NULL );
    pthread_create(&thread2, NULL, &consume, NULL );
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return 0;
}
