#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/time.h>

int main(int argc, char** argv)
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	printf("tv_sec = %d, tv_usec = %d, tz_minuteswest = %d, tz_dsttime = %d\n", 
			tv.tv_sec, tv.tv_usec, tz.tz_minuteswest, tz.tz_dsttime) ;
	
	return 0;
}
