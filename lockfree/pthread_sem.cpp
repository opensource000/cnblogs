#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

sem_t binSem;

void* helloWorld(void* arg) 
{
    while(1) 
	{
        // Wait semaphore
        sem_wait(&binSem);
        printf("Hello World\n");
     }
}

int main(int argc, char** argv) 
{
    // Result for System call
    int res = 0;

    // Initialize semaphore
    sem_init(&binSem, 0, 0);

    // Create thread
    pthread_t thdHelloWorld;
    pthread_create(&thdHelloWorld, NULL, helloWorld, NULL);

    while(1) 
	{
        // Post semaphore
        sem_post(&binSem);
        printf("In main, sleep several seconds.\n");
        sleep(1);
     }

    // Wait for thread synchronization
    void *threadResult;
    pthread_join(thdHelloWorld, &threadResult);

    return 0;
}
