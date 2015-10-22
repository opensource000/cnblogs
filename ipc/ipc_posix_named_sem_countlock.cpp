#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>           
#include <sys/stat.h>    
#include <errno.h>
#include <string.h>

sem_t* namedSem;
#define FILENAME "/tmp/count_named_sem.txt"
#define MUTEXNAME "my_named_sem"

int main(int argc, char** argv) 
{
    int fd, inum, iloop;
    if (argc != 2)
    {
        printf("usage: ./ipc_posix_sem_countlock <loopnum>\n");
        return 0;
    }
    namedSem = sem_open(MUTEXNAME, O_CREAT|O_EXCL, 0644, 1);
    if (SEM_FAILED == namedSem)
    {
        if (errno != EEXIST)
        {
            printf("sem_open error : %s\n", strerror(errno));
            return -1;
        }
        printf("sem_open %s exist! so open\n", MUTEXNAME);
        namedSem = sem_open(MUTEXNAME, O_RDWR);
    }
    printf("sem_open succ\n", MUTEXNAME);
    
    iloop = atoi(argv[1]);
    fd = open(FILENAME, O_RDWR);
    for (int i = 0; i < iloop; ++i)
    {
        sem_wait(namedSem);
        lseek(fd, 0, SEEK_SET);
        read(fd, &inum, sizeof(int));
        usleep(1000);
        inum++;
        lseek(fd, 0, SEEK_SET);
        write(fd, &inum, sizeof(int));
        sem_post(namedSem);
    }
    printf("pid %d countlock down\n", getpid());
    return 0;
}
