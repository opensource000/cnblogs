#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{
	const char* wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	time_t timep;
	struct tm* p;
	time(&timep);
	p = localtime(&timep);
	printf("curday = %d-%d-%d\n", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
	printf("curweek = %s, curtime = %d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
	return 0;
}
