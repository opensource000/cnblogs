#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

int main(int argc, char** argv)
{
    FILE *fp = NULL;
    int i = 20; 
    if ((fp = fopen("./file_lock.test", "r+b")) == NULL) //打开文件
	{
        printf("file open error!\n");
		exit(0);
	}
    if (flock(fp->_fileno, LOCK_EX) != 0) //给该文件加锁
        printf("file lock by others\n");
    while(1) //进入循环,加锁时间为20秒,打印倒计时
    {   
        printf("in a, %d\n", i--); 
        sleep(1);
        if (i == 0)
            break;
    }   
    fclose(fp); //20秒后退出,关闭文件
    flock(fp->_fileno, LOCK_UN); //文件解锁
    return 0;
}

