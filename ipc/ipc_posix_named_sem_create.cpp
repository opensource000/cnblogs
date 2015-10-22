#include <stdio.h> 
#include <stdlib.h> 
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
    int fd, inum = 0;
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
    
    fd = open(FILENAME, O_RDWR|O_CREAT|O_TRUNC, 0777);
    write(fd, &inum, sizeof(int));
    return 0;
}
