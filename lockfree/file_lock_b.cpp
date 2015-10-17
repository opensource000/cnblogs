#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

int main(int argc, char** argv)
{
    FILE *fp = NULL;
    int i = 20; 
    if ((fp = fopen("./file_lock.test", "r+b")) == NULL) 
	{
        printf("file open error!\n");
		exit(0);
	}
    flock(fp->_fileno, LOCK_EX);
    while(1) //����ѭ��,����ʱ��Ϊ20��,��ӡ����ʱ
    {   
        printf("in b, %d\n", i--); 
        sleep(1);
		if (i == 0)
            break;
    }   
    fclose(fp); //20����˳�,�ر��ļ�
    flock(fp->_fileno, LOCK_UN); //�ļ�����
    return 0;
}
