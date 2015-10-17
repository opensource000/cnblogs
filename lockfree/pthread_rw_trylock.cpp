#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>
 
static pthread_rwlock_t rwlock; //¶ÁÐ´Ëø¶ÔÏó

int count = 0;

void *thread_function_read(void *arg)
{
	int print_count = 0;
    while(1)
    {
        if (pthread_rwlock_tryrdlock(&rwlock) == 0)
		{
			printf("************************%d, read count %d\n", pthread_self(), count);
			sleep(1);
			pthread_rwlock_unlock(&rwlock);
			usleep(100);
		}
        else
		{
			print_count++;
			if (print_count % 10 == 0)
			{
				printf("I have try!But i can`t lock the rdlock!\n");
				print_count = 0;
			}
			
			usleep(100);
		}
    }
    
    return NULL;
}

void *thread_function_write(void *arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        count++;
        printf("************************%d, write count %d\n", pthread_self(), count);
        sleep(5);
        pthread_rwlock_unlock(&rwlock);
		usleep(100);
    }
    return NULL;
}
   
int main(int argc, char *argv[])
{
    pthread_t rpthread1, rpthread2, wpthread;

    pthread_rwlock_init(&rwlock,NULL);

    pthread_create(&rpthread1, NULL, thread_function_read, NULL);
    pthread_create(&rpthread2, NULL, thread_function_read, NULL);
    pthread_create(&wpthread, NULL, thread_function_write, NULL);

    pthread_join(rpthread1, NULL);           
    pthread_join(rpthread2, NULL);           
    pthread_join(wpthread, NULL);           
               
    pthread_rwlock_destroy(&rwlock);          
    exit(EXIT_SUCCESS);
}
