#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  

int main(int argc, char** argv)  
{   
    if (argc < 2)
    {
        printf("usage:./snprintf_perfect xxxx\n");
        return -1;
    }
    char buffer[16];
    size_t max_len = sizeof(buffer) - 1;
    int len = snprintf(buffer, max_len, "%s", argv[1]);
    if ((len < 0) || (len > max_len))
    {
        printf("overflow!!\n");
    }
    else
    {
        buffer[max_len] = 0;
        printf("%s\n", buffer);
    }
    
	return 0;
}  
