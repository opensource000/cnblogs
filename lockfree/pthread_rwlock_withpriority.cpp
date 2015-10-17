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
    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("************************%d, read count %d\n", pthread_self(), count);
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
		//usleep(100);
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
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
		usleep(100);
    }
    return NULL;
}
   
int main(int argc, char *argv[])
{
    pthread_t rpthread1, rpthread2, wpthread;
    
    pthread_rwlockattr_t attr;    
    pthread_rwlockattr_setkind_np(&attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&rwlock, &attr);

    pthread_create(&rpthread1, NULL, thread_function_read, NULL);
    pthread_create(&rpthread2, NULL, thread_function_read, NULL);
    pthread_create(&wpthread, NULL, thread_function_write, NULL);

    pthread_join(rpthread1, NULL);           
    pthread_join(rpthread2, NULL);           
    pthread_join(wpthread, NULL);           
               
    pthread_rwlock_destroy(&rwlock);          
    exit(EXIT_SUCCESS);
}
