#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <limits.h>  
#include <string.h> 
#include <signal.h>

int count = 1;
void deal_sig(int signum)
{
	switch(signum)
	{
	case 1: // SIGHUP
		printf("signal SIGHUP cached\n");
		break;
	case 2: // SIGINT
		printf("signal SIGINT cached\n");
		break;
	case 3: // SIGQUIT
		printf("signal SIGQUIT cached\n");
		break;
	case 10: // SIGUSR1
		printf("signal SIGUSR1 cached, count = %d\n", count);
		break;
	case 12: // SIGUSR2
		printf("signal SIGUSR2 cached, count = %d\n", count);
		break;
	}
	return;
}
  
int main(int argc, char** argv)  
{  
   signal(SIGHUP, deal_sig);
   signal(SIGINT, deal_sig);
   signal(SIGQUIT, deal_sig);
   signal(SIGUSR1, deal_sig);
   signal(SIGUSR2, deal_sig);
   signal(SIGKILL, SIG_IGN);
   signal(SIGSEGV, SIG_DFL);
   while(1)
   {
	   count++;
	   sleep(1);
   }
   return 0;
}  
