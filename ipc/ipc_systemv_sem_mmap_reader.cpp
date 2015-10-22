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

int sem_p(int sem_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0; // 信号量编号
    sem_buf.sem_op = -1; // P操作
    sem_buf.sem_flg = 0;
    //sem_buf.sem_flg = SEM_UNDO; // 系统退出前未释放信号量，系统自动释放
    if (semop(sem_id, &sem_buf, 1) == -1) 
    {  
        perror("Sem P operation");  
        exit(1);  
    }  
    return 0;  
}

int sem_v(int sem_id)
{
    struct sembuf sem_buf;  
    sem_buf.sem_num = 0;  
    sem_buf.sem_op = 1; // V操作
    sem_buf.sem_flg = 0;
    //sem_buf.sem_flg = SEM_UNDO;  
    if (semop(sem_id, &sem_buf, 1) == -1) 
    {  
        perror("Sem V operation");  
        exit(1);  
    }  
    return 0;  
}

int main(int argc, char** argv) 
{
    const char* name = "/dev/shm/my_systemv_shm2";
    key_t key = ftok(name,0);
    if (key == -1)
    {
        perror("ftok error");
        return -1;
    }
    int semid = semget(key, 1, 0666);  
    if (-1 == semid)
    {
        printf("semget get error: %s\n", strerror(errno));
    }
    else
    {
        printf("semget create succ\n");
    }
    
    union semun un;
    printf("semid = %d, semvalue = %d\n", semid, semctl(semid, 0, GETVAL, 0));
    
    while(1)
    {
        // Wait semaphore
        sem_p(semid);
        printf("Hello World\n");
        printf("semid = %d, semvalue = %d\n", semid, semctl(semid, 0, GETVAL, 0));
    }
    
    return 0;
}
