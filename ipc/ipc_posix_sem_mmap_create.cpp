#include <sys/mman.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h> 
#include <semaphore.h> 

int main(int argc, char** argv) 
{
    sem_t* shm_sem;

    const char* name = "/dev/shm/my_systemv_shm1";
    key_t key = ftok(name,0);
    if (key == -1)
    {
        perror("ftok error");
        return -1;
    }
    int shm_id=shmget(key, sizeof(sem_t), IPC_CREAT);
    if(shm_id == -1)
    {
        perror("shmget error");
        return -1;
    }
    shm_sem=(sem_t*)shmat(shm_id,NULL,0);

    // Initialize semaphore
    sem_init(shm_sem, 1, 0); // pshared = 1
    return 0;
}
