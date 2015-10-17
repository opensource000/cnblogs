#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void* consume(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        printf("************************consume begin lock\n");  
        printf("************************consumed %d\n",count);  
        count++;
        sleep(2);
        printf("************************consume over lock\n"); 
        pthread_mutex_unlock(&mutex); 
        printf("************************I'm out of pthread_mutex\n"); 
        sleep(1);
    }
    
    return NULL;
}

void* produce( void * arg )
{
    while(1)
    {
        pthread_mutex_lock(&mutex );
        printf("product begin lock\n");
        printf("produced %d\n", count);
        printf("product over lock\n");
        pthread_mutex_unlock(&mutex );
        printf("I'm out of pthread_mutex\n");
        sleep(1);
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
