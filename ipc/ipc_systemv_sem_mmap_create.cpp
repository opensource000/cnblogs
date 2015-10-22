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
#include <sys/sem.h>

union semun 
{  
    int              val;    /* Value for SETVAL */  
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */  
    unsigned short  *array;  /* Array for GETALL, SETALL */  
    struct seminfo  *__buf;  
};  

int main(int argc, char** argv) 
{
    const char* name = "/dev/shm/my_systemv_shm2";
    union semun un;
    
    key_t key = ftok(name,0);
    if (key == -1)
    {
        perror("ftok error");
        return -1;
    }
    int semid = semget(key, 1, 0666|IPC_CREAT|IPC_EXCL);  
    if (-1 == semid)
    {        
        if (errno != EEXIST)  
        {  
            printf("semget error: %s\n", strerror(errno));
            return -1;  
        }
        semid = semget(key, 0, 0666);
        printf("semget get succ\n");
    }
    else
    {
        printf("semget create succ\n");
        un.val = 1;
        if (semctl(semid, 0, SETVAL, un) == -1)
        {
            printf("semctl error: %s\n", strerror(errno));
            return -1;
        }
    }
    struct semid_ds buf;
    un.buf = &buf;
    int ret = semctl(semid, 0, IPC_STAT, un);
    if (-1 == ret)
    {
        printf("semctl error: %s\n", strerror(errno));
        return -1;
    }
    printf("semid = %d, semvalue = %d\n", semid, un.buf->sem_nsems);
    
    return 0;
}
